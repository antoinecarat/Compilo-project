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
//#include <regex>
#include <vector>

using namespace std;


Tree* A[50];


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
  //S0
  forest[0] = gen_conc(gen_star(gen_conc(gen_conc(gen_conc(gen_atom("N", 0, false),
                                                     gen_atom("\'->\'", 0, true)
                                                     ),
                                             gen_atom("E", 0, false)
                                             ),
                                     gen_atom("\',\'", 1, true)
                                     )),
                      gen_atom("\';\'", 0, true)
                      );
  //N0
  forest[1] = gen_atom("\'IDNTER\'", 2, true);
  //E0
  forest[2] = gen_conc(gen_atom("T", 0, false),
                     gen_star(gen_conc(gen_atom("\'+\'", 0, true),
                                     gen_atom("T", 3, false)
                                    ))
                    );
  //T0
  forest[3] = gen_conc(gen_atom("F", 0, false),
                     gen_star(gen_conc(gen_atom("\'.\'", 0, true),
                                     gen_atom("F", 4, false)
                                     ))
                     );
  //F0
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
}

Tree* getTreeForId(string id)
{
  if (id == "S")
  {
    return A[0];
  } else if (id == "N")
  {
    return A[1];
  } else if (id == "E")
  {
    return A[2];
  } else if (id == "T")
  {
    return A[3];
  } else if (id == "F")
  {
    return A[4];
  } else
  {
    return NULL;
  }
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
  cout << "Scan with offset : " << offset << endl;
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
  

  cout << "----- Analyse de : " << root->getType() << endl;
  if (root->getType() == "Conc") {
   	if (g0_analyse(filename, root->getLeft(), offset))
   	{
   		cout << "                  Conc à droite" << endl;
   		bool caca = g0_analyse(filename, root->getRight(), offset);
   		cout << "                ------ Sortie de Conc (" << (caca ? "true" : "false") << ")" << endl;
   		return caca;
   	} else
   	{
        cout << "                ------ Sortie de Conc (false) ------" << endl;
   		return false;
   	}
  } else if (root->getType() == "Union") {
    if (g0_analyse(filename, root->getLeft(), offset))
    {
        cout << "                ------ Sortie de Union (true) ------" << endl;
    	return true;
    } else
    {
    	cout << "                  Union à droite" << endl;
   		return g0_analyse(filename, root->getRight(), offset);
    }
  } else if (root->getType() == "Star") {
  		cout << "                                            Un while sauvage apparait et m'aspire." << endl;
    	while (g0_analyse(filename, root->getElt(), offset)) {
    		cout << "                                            Je suis dans le while, aidez moi." << endl;
    	}
   		cout << "                ------ Sortie de Star (true) ------" << endl;
    	return true;
  } else if (root->getType() == "Un") {
    	if (g0_analyse(filename, root->getElt(), offset)) {}
   		cout << "                ------ Sortie de Un (true) ------" << endl;
    	return true;
  } else if (root->getType() == "Atom") {
    cout << "----- ROOT : " << root->getCode() << endl;
    //cout << "   code: " << root->getCode() << endl;
    //cout << "   terminal? " << (root->getTerminal() ? "OUI" : "NON") << endl;
    //cout << "   action: " << root->getAction() << endl;
    cout << "----- SCANNED : " << scanned->getUnit() << " ; " << scanned->getCode() << endl;
    //cout << "   chaine: " << scanned->getUnit() << endl;
    //cout << "   code: " << scanned->getCode() << endl;
    //cout << "   terminal? " << (scanned->getTerminal() ? "OUI" : "NON") << endl;
    //cout << "   action: " << scanned->getAction() << endl;
    if (root->getTerminal())
    {
      if (root->getCode() == scanned->getCode()) {
        if (root->getAction() != 0) {
          // int actionType;
          // stringstream s;
          // s << this->uniteLexicale["action"];
          // s >> actionType;
          // AtomType aType = this->uniteLexicale["code"] == "IDNTER" ? NTER : TER;
          // G0Action(op, actionType, aType);
        }
        //Rescan
        cout << "Rescan !" << endl;
        offset += scanned->getUnit().size();
		    if (scanned->getAction() != 0)
		    {
		      ++offset; //one for the #
		      offset += scanned->getAction()/10 + 1; //n for the number of digits in action
		    }
		    cout << "Added: " << scanned->toString() << endl;
        scanned = g0_scan(filename, offset);
        cout << "                ------ Sortie de Atom TERM (true) ------" << endl;
        return true;
      } else {
        cout << "                ------ Sortie de Atom TERM (false) ------" << endl;
        return false;
      }
    } else
    {
      if (g0_analyse(filename, getTreeForId(root->getCode()), offset))
      {
        if (root->getAction() != 0) {
          // int actionType1;
          // stringstream s1;
          // s1 << this->uniteLexicale["action"];
          // s1 >> actionType1;
          // AtomType aType = this->uniteLexicale["code"] == "IDNTER" ? NTER : TER;
          // G0Action(op, actionType1, aType);
        }
        cout << "                ------ Sortie de Atom NTERM (true) -----" << endl;
        return true;
      }
    }
    cout << "                ------ Sortie ------" << endl;
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
    for (int i = 5; i < 50 && A[i] != NULL; ++i)
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