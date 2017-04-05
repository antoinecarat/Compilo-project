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
  //N
  forest[1] = gen_atom("\'IDNTER\'", 2, true);
  //E
  forest[2] = gen_conc(gen_atom("T", 0, false),
                     gen_star(gen_conc(gen_atom("\'+\'", 0, true),
                                     gen_atom("T", 3, false)
                                    ))
                    );
  //T
  forest[3] = gen_conc(gen_atom("F", 0, false),
                     gen_star(gen_conc(gen_atom("\'.\'", 0, true),
                                     gen_atom("F", 4, false)
                                     ))
                     );
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

  ifstream file(filename, ios::in);
  file.seekg(offset);

  string unit;
  string lex_unit;
  int cmp;

  if(file >> unit)//TODO: Replace this by getline
  {
    cout << "\n-->> Read : " << unit << endl;
    cmp = 0;
    lex_unit = "";
    lex_unit += unit.at(cmp);
    if (unit.size() == 1)
    {
      if(is_symbol(lex_unit))
      {
        return new Lexical_unit(lex_unit, lex_unit, true);
      }
      return new Lexical_unit(lex_unit, "IDNTER", false);
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
            cout << "Action:" << action << endl;
            action += unit.at(++cmp);
          }
          action_num = atoi(action.c_str());
        }
        return new Lexical_unit(lex_unit, "ELTER", true, action_num);
      } else
      {
        string double_unit = lex_unit;
        if(unit.size() - cmp > 1)
        {
          double_unit += unit.at(++cmp);
          if (is_symbol(double_unit))
          {
            return new Lexical_unit(double_unit, double_unit, true);
          } else
          {
            --cmp;
          }
        }
        if (is_symbol(lex_unit))
        {
          return new Lexical_unit(lex_unit, lex_unit, true);
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
            tmp += unit.at(++cmp);
            tmp2 = tmp;
            if(unit.size() - cmp > 1)
            {
              tmp2 += unit.at(++cmp);
            }
          }
          if (tmp.compare("#") == 0)
          {
            cmp -= 2;
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
                cout << "Action:" << action << endl;
                action += unit.at(++cmp);
              }
              action_num = atoi(action.c_str());
            }
          }
          
          return new Lexical_unit(lex_unit, "IDNTER", false, action_num);
        }
      }
    }
  }

  file.close();

  return NULL;
}

//Appelle le scan, et execute les actions pour construire les arbres de la GPL.
bool g0_analyse(string filename, Tree* tree, int offset)
{
  Lexical_unit* scanned = g0_scan(filename, offset);
  Node* root = tree->getRoot();
  bool ana = false;

  //analyse
  /*if (root->getType() == "Conc") {
    ana = g0_analyse(filename, root->getLeft(), offset) && g0_analyse(filename, root->getRight(), offset);
  } else if (root->getType() == "Union") {
      ana = g0_analyse(filename, root->getLeft(), offset) || g0_analyse(filename, root->getLeft(), offset);
  } else if (root->getType() == "Star") {
      ana = true;
      while (g0_analyse(filename, root->getElt(), offset)) {}
  } else if (root->getType() == "Un") {
      ana = true;
      if (g0_analyse(filename, root->getElt(), offset)) {}
  } else if (root->getType() == "Atom") {
    cout << "end of branch" << endl;

    //TODO: Controler l'atom

    offset += scanned->getUnit().size();
    if (scanned->getAction() != 0)
    {
      ++offset; //one for the #
      offset += scanned->getAction()/10 + 1; //n for the number of digits in action
    }
    cout << "Added: " << scanned->toString() << endl;
    scanned = g0_scan(filename, offset);
    //ana = true;
  }

  cout << "#######################################################################################################" << endl;*/

  while (scanned != NULL)
  {
    offset += scanned->getUnit().size();
    if (scanned->getAction() != 0)
    {
      ++offset; //one for the #
      offset += scanned->getAction()/10 + 1; //n for the number of digits in action
    }
    cout << "Added: " << scanned->toString() << endl;
    scanned = g0_scan(filename, offset);
  }

  return ana;
}

int main(void)
{  
  Tree* A[50];
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

  if (g0_analyse("gpl.txt", A[0], 0))
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