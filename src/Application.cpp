#include "Tree.hpp"
#include "Node.hpp"
#include "Atom.hpp"
#include "Conc.hpp"
#include "Union.hpp"
#include "Star.hpp"
#include "Un.hpp"
#include "Lexical_unit.hpp"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <stack>
#include <map>
#include <vector>

using namespace std;


Tree* A[50];
map<string, int> binding;
stack<Tree*> g0_stack;


Tree* gen_conc(Tree* left, Tree* right)
{
  return new Tree(new Conc(left, right));
}

Tree* gen_union(Tree* left, Tree* right)
{
  return new Tree(new Union(left, right));
}

Tree* gen_star(Tree* star)
{
  return new Tree(new Star(star));
}

Tree* gen_un(Tree* un)
{
  return new Tree(new Un(un));
}

Tree* gen_atom(std::string code, int action, bool terminal)
{
  return new Tree(new Atom(code, action, terminal));
}

void gen_forest(Tree* forest[])
{
  //S
  forest[0] = gen_conc(gen_star(gen_conc(gen_conc(gen_conc(gen_atom("N", 0, false),
                                                     gen_atom("\'->\'", 0, true)
                                                     ),
                                             gen_atom("E", 0, false)
                                             ),
                                     gen_atom("\',\'", 1, true)
                                     )),
                      gen_atom("\';\'", 0, true)
                      );
  binding.insert ( std::pair<string,int>("S", 0));

  //N
  forest[1] = gen_atom("\'IDNTER\'", 2, true);
  binding.insert ( std::pair<string,int>("N", 1));

  //E
  forest[2] = gen_conc(gen_atom("T", 0, false),
                     gen_star(gen_conc(gen_atom("\'+\'", 0, true),
                                     gen_atom("T", 3, false)
                                    ))
                    );
  binding.insert ( std::pair<string,int>("E", 2));

  //T
  forest[3] = gen_conc(gen_atom("F", 0, false),
                     gen_star(gen_conc(gen_atom("\'.\'", 0, true),
                                     gen_atom("F", 4, false)
                                     ))
                     );
  binding.insert ( std::pair<string,int>("T", 3));

  //F
  forest[4] = gen_union(gen_atom("\'IDNTER\'", 5, true),
                      gen_union(gen_atom("\'ELTER\'", 5, true),
                               gen_union(gen_conc(gen_conc(gen_atom("\'(\'", 0, true),
                                                        gen_atom("E", 0, false)
                                                        ),
                                                gen_atom("\')\'", 0, true)
                                                ),
                                        gen_union(gen_conc(gen_conc(gen_atom("\'[\'", 0, true),
                                                                 gen_atom("E", 0, false)
                                                                ),
                                                         gen_atom("\']\'", 6, true)
                                                        ),
                                                 gen_conc(gen_conc(gen_atom("\'(|\'", 0, true),
                                                                 gen_atom("E", 0, false)
                                                                ),
                                                         gen_atom("\'|)\'", 7, true)
                                                        )
                                                 )
                                        )
                               )
                      );
  binding.insert ( std::pair<string,int>("F", 4));
}

Tree* getTreeForId(string id)
{
  return A[binding[id]];
}

int getLastIndex()
{
	int i = 0;
	while (i<50 && A[i] != NULL)
	{
		++i;
	}
	return i;
}

bool is_symbol(string unit)
{
  vector<string> symbolsTable;
  symbolsTable.push_back("->");
  symbolsTable.push_back(".");
  symbolsTable.push_back("+");
  symbolsTable.push_back("[");
  symbolsTable.push_back("]");
  symbolsTable.push_back("(|");
  symbolsTable.push_back("|)");
  symbolsTable.push_back(",");
  symbolsTable.push_back(";");


  for (int i = 0; i < symbolsTable.size(); ++i)
  {
    if (unit.compare(symbolsTable.at(i)) == 0)
    {
      return true;
    }
  }
  return false;
}

bool is_numeric(string unit)
{
  return (unit.find_first_not_of( "0123456789" ) == string::npos);
}

//Donne l'unité lexicale suivante
Lexical_unit* g0_scan(string filename, int offset)
{
  //cout << "Scan with offset : " << offset << endl;
  ifstream file(filename, ios::in);

  file.seekg(offset);

  char c;
  string k = "";
  file.get(c);
  k += c;
  if (k == "\n")
  {
  	return new Lexical_unit("eol", "eol", true);
  } else
  {
  	file.seekg(offset);
  }

  string unit;
  string lex_unit;
  int cmp;

  if(file >> unit)//TODO: Replace this by getline to manage spaces
  //if (file.getline(unit, 9999999))
  {
    cmp = 0;
    lex_unit = "";
    lex_unit += unit.at(cmp);
    if (unit.size() == 1)
    {
      if(is_symbol(lex_unit))
      {
      	string code = "\'";
       	code += lex_unit;
       	code += "\'";
        return new Lexical_unit(lex_unit, code, true);
      }
      return new Lexical_unit(lex_unit, "\'IDNTER\'", false);
    } else
    {
      if (lex_unit.compare("'") == 0)
      {
        string tmp = "";
        tmp += unit.at(++cmp);
        while(tmp.compare("'") != 0 && cmp < unit.size() - 1)
        {
          lex_unit += tmp;
          tmp = "";
          tmp += unit.at(++cmp);
        }
        lex_unit += tmp; // add '
        //Test if there is an action
        string action;
        action="";
        action += unit.at(++cmp);
        int action_num = 0;

        if (action.compare("#") == 0)
        {
          action="";
          action += unit.at(++cmp);
          while(is_numeric(action))
          {
            action += unit.at(++cmp);
          }
          action_num = atoi(action.c_str());
        }
        return new Lexical_unit(lex_unit, "\'ELTER\'", true, action_num);
      } else
      {
        string double_unit = lex_unit;
        if(unit.size() - cmp > 1)
        {
          double_unit += unit.at(++cmp);
          if (is_symbol(double_unit))//
          {
          	string code = "\'";
          	code += double_unit;
          	code += "\'";
            return new Lexical_unit(double_unit, code, true);
          } else
          {
            --cmp;
          }
        }
        if (is_symbol(lex_unit))//
        {
          string code = "\'";
          code += lex_unit;
          code += "\'";
          return new Lexical_unit(lex_unit, code, true);
        } else
        {
          int action_num = 0;

          string tmp = "";
          tmp += unit.at(++cmp);
          string tmp2 = tmp;
          if(unit.size() - cmp > 1)
          {
            tmp2 += unit.at(++cmp);

          }
          while(tmp.compare("#") != 0 && tmp.compare("'") != 0 && !is_symbol(tmp) && cmp < unit.size() - 1)
          {
            if(is_symbol(tmp2))
            {
              --cmp;
              break;
            }
            lex_unit += tmp;
            tmp = "";
            tmp += unit.at(cmp);
            tmp2 = tmp;
            if(unit.size() - cmp > 1)
            {
              tmp2 += unit.at(++cmp);
            }
          }
          cmp -= 2;
          if (tmp.compare("#") == 0)
          {
            //Test if there is an action
            string action;
            action="";
            action += unit.at(++cmp);

            if (action.compare("#") == 0)
            {
              action="";
              action += unit.at(++cmp);
              while(is_numeric(action))
              {
                //cout << "Action:" << action << endl;
                action += unit.at(++cmp);
              }
              action_num = atoi(action.c_str());
            }
          }
          
          return new Lexical_unit(lex_unit, "\'IDNTER\'", false, action_num);
        }
      }
    }
  }

  file.close();

  return NULL;
}

void g0_action(Node* root, Lexical_unit* scanned)
{
	Tree* t1;
	Tree* t2;
	if (root->getAction() == 1) // Action 1 : créer arbre
	{
		//cout << "Action 1 !" << endl;
	    if (!g0_stack.empty()) {
	        t1 = g0_stack.top();
	        //cout << "ARBRE : " << g0_stack.top()->toString(0) << endl;
	        g0_stack.pop();
	        if (!g0_stack.empty())
	        {
	            t2 = g0_stack.top();
	        	//cout << "NT : " << g0_stack.top()->getRoot()->getCode() << endl;
	        	g0_stack.pop();

	        	//foret[t2->getCode()] = t1;//FIXME
				binding.insert ( std::pair<string,int>(t2->getRoot()->getCode(), getLastIndex()));
				A[getLastIndex()] = t1;
	        }
	        //cout << "empty stack" << endl;
	    }
	} else if (root->getAction() == 2) // Action 2 : Créer Terminal
	{
		//cout << "Action 2 !" << endl;
        g0_stack.push(gen_atom (scanned->getUnit(), scanned->getAction(), scanned->getTerminal()));
	} else if (root->getAction() == 3) // Action 3 : Créer union
    {
		//cout << "Action 3 !" << endl;
		if (!g0_stack.empty()) {
            t1 = g0_stack.top();
            g0_stack.pop();
            if (!g0_stack.empty()) {
                t2 = g0_stack.top();
                g0_stack.pop();
                g0_stack.push(gen_union(t1, t2));
            }
        }
        //cout << "empty stack" << endl;
    } else if (root->getAction() == 4) // Action 4 : Créer Conc
    {
		//cout << "Action 4 !" << endl;
		if (!g0_stack.empty()) {
            t1 = g0_stack.top();
            g0_stack.pop();
            if (!g0_stack.empty()) {
                t2 = g0_stack.top();
                g0_stack.pop();
                g0_stack.push(gen_conc(t1, t2));
            }
        }
        //cout << "empty stack" << endl;
    } else if (root->getAction() == 5) // Action 5 : Créer terminal / Non terminal
    {
		//cout << "Action 5 !" << endl;
		g0_stack.push(gen_atom (scanned->getUnit(), scanned->getAction(), scanned->getTerminal()));
    } else if (root->getAction() == 6) // Action 6 : Créer star
    {
		//cout << "Action 6 !" << endl;
		if (!g0_stack.empty()) {
            t1 = g0_stack.top();
            g0_stack.pop();
            g0_stack.push(gen_star(t1));
        }
        //cout << "empty stack" << endl;
    } else if (root->getAction() == 7) // Action 7 : Créer Un
    {
		//cout << "Action 7 !" << endl;
		if (!g0_stack.empty()) {
            t1 = g0_stack.top();
            g0_stack.pop();
            g0_stack.push(gen_un(t1));
        }
        //cout << "empty stack" << endl;
    }

    // cout << "Post-traitement : " << endl;
    // cout << g0_stack.top()->toString(0) << endl;

}

//Appelle le scan, et execute les actions pour construire les arbres de la GPL.
bool g0_analyse(string filename, Tree* tree, int &offset)
{
  Lexical_unit* scanned = g0_scan(filename, offset);
  if (scanned->getUnit() == "eol")
  {
	++offset;
   	scanned = g0_scan(filename, offset);
  }
  Node* root = tree->getRoot();
  bool ana = false;
  

  //cout << "----- Analyse de : " << root->getType() << endl;
  if (root->getType() == "Conc") {
   	if (g0_analyse(filename, root->getLeft(), offset))
   	{
   		return g0_analyse(filename, root->getRight(), offset);
   	} else
   	{
        return false;
   	}
  } else if (root->getType() == "Union") {
    if (g0_analyse(filename, root->getLeft(), offset))
    {
        return true;
    } else
    {
    	return g0_analyse(filename, root->getRight(), offset);
    }
  } else if (root->getType() == "Star") {
  		while (g0_analyse(filename, root->getElt(), offset)) {}
   		return true;
  } else if (root->getType() == "Un") {
    	if (g0_analyse(filename, root->getElt(), offset)) {}
   		return true;
  } else if (root->getType() == "Atom") {
    //cout << "----- ROOT : " << root->getCode() << endl;
    //cout << "   terminal? " << (root->getTerminal() ? "OUI" : "NON") << endl;
    //cout << "   action: " << root->getAction() << endl;
    //cout << "----- SCANNED : " << scanned->getUnit() << " ; " << scanned->getCode() << endl;
    //cout << "   chaine: " << scanned->getUnit() << endl;
    //cout << "   code: " << scanned->getCode() << endl;
    //cout << "   terminal? " << (scanned->getTerminal() ? "OUI" : "NON") << endl;
    //cout << "   action: " << scanned->getAction() << endl;
    if (root->getTerminal())
    {
      //cout << (root->getCode() == scanned->getCode()) << endl;
      if (root->getCode() == scanned->getCode()) {
        if (root->getAction() != 0) {
        	//cout << "Calling Action n " << root->getAction() << endl;
          g0_action(root, scanned);
        }
        //Rescan
        //cout << "Rescan !" << endl;
        offset += scanned->getUnit().size();
	    if (scanned->getAction() != 0)
	    {
	      ++offset; //one for the #
	      offset += scanned->getAction()/10 + 1; //n for the number of digits in action
	    }
        scanned = g0_scan(filename, offset);
        //cout << "-------------------->>>>>>>>>>>>>>>>>>" << endl;
        return true;
      } else {
        return false;
      }
    } else
    {
      if (g0_analyse(filename, getTreeForId(root->getCode()), offset))
      {
        if (root->getAction() != 0) {
          g0_action(root, scanned);
        }
        return true;
      }
    }
  }

  /*while (scanned != NULL)
  {
  	if (scanned->getUnit() == "eol")
  	{
  		++offset;
  	} else
  	{
	    offset += scanned->getUnit().size();
	    if (scanned->getAction() != 0)
	    {
	      ++offset; //one for the #
	      offset += scanned->getAction()/10 + 1; //n for the number of digits in action
	    }
	    cout << "Added: " << scanned->toString() << endl;
	}
    scanned = g0_scan(filename, offset);
  }*/

  return ana;
}

int main(void)
{  
  
  for (int i = 0; i < 50; ++i)
  {
    A[i] = NULL;
  }

  cout << ">> Règles d'une grammaire :" << endl;
  gen_forest(A);
  for (int i = 0; i < 5; ++i)
  {
     cout << "A[" << i << "] :" << endl;
     cout << A[i]->toString(0) << endl;
     cout << "\n\n" << endl; 
  }

  int offset = 0;

  if (g0_analyse("gpl.txt", A[0], offset))
  {
    cout << ">> Règles de G0 :" << endl;
    for (int i = 5; i < getLastIndex(); ++i)
    {
      cout << "A[" << i << "] :" << endl;
      cout << A[i]->toString(0) << endl;
      cout << "\n\n" << endl; 
    }
  } else {
    cout << "Le contenu du fichier n'est pas une grammaire." << endl;
  }  


  return 0;
}