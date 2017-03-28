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
  forest[0] = gen_conc(gen_star(gen_conc(gen_conc(gen_conc(gen_atom("N", 0, false),
                                                     gen_atom("F", 0, false)
                                                     ),
                                             gen_atom("E", 0, false)
                                             ),
                                     gen_atom(",", 1, true)
                                     )),
                      gen_atom(";", 1, true)
                      );
  forest[1] = gen_atom("I", 0, false);
  forest[2] = gen_conc(gen_atom("I", 0, false),
                     gen_star(gen_conc(gen_atom("+", 0, true),
                                     gen_atom("T", 0, false)
                                    ))
                    );
  forest[3] = gen_conc(gen_atom("F", 0, false),
                     gen_star(gen_conc(gen_atom(".", 1, true),
                                     gen_atom("F", 0, false)
                                     ))
                     );
  forest[4] = gen_union(gen_atom("IDNTER", 0, false),
                      gen_union(gen_atom("ELTER", 0, false),
                               gen_union(gen_conc(gen_conc(gen_atom("(", 0, true),
                                                        gen_atom("E", 0, false)
                                                        ),
                                                gen_atom(")", 0, true)
                                                ),
                                        gen_union(gen_conc(gen_conc(gen_atom("[", 0, true),
                                                                 gen_atom("E", 0, false)
                                                                ),
                                                         gen_atom("]", 0, true)
                                                        ),
                                                 gen_conc(gen_conc(gen_atom("(\\", 0, true),
                                                                 gen_atom("E", 0, false)
                                                                ),
                                                         gen_atom("\\)", 0, true)
                                                        )
                                                 )
                                        )
                               )
                      );
}

bool is_symbol(string unit)
{
  vector<string> symbolsTable;
  symbolsTable.push_back("-");
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

vector<Lexical_unit*> g0_scan(string filename)
{

  ifstream file(filename, ios::in);
  vector<Lexical_unit*> lex_units;

  if(file)
  {
    string unit;
    string lex_unit;
    int cmp;
    while(file >> unit)
    {
      while (unit.length() > 0)
      {
        cout << "--------\n" << "Unit : " << unit << endl;
        cmp = 0;
        lex_unit = "";
        lex_unit += unit.at(cmp);
        cout << "Lex_unit : " << lex_unit << endl;
        if (unit.size() == 1)
        {
          cout << "SIZE 1" << endl;
          lex_units.push_back(new Lexical_unit(lex_unit, false));
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
            lex_units.push_back(new Lexical_unit(lex_unit, true));
          } else if (is_symbol(lex_unit))
          {
            lex_units.push_back(new Lexical_unit(lex_unit, false));
          } else
          {
            string tmp = "";
            tmp += unit.at(++cmp);
            while(tmp.compare("'") != 0 && !is_symbol(tmp) && cmp < unit.size() - 1)
            {
              lex_unit += tmp;
              tmp = "";
              tmp += unit.at(++cmp);
            }
            lex_units.push_back(new Lexical_unit(lex_unit, false));
          }
          cout << "Add : " << lex_unit << endl;
          unit = unit.substr(++cmp);
        }
      }
    }

    file.close();

  }
  else {
    cerr << "Impossible d'ouvrir le fichier !" << endl;
  }

  return lex_units;
}

//Appelle le scan, et execute les actions pour construire les arbres de la GPL.
void g0_analyse(string filename, Tree* forest[])
{
  
}


int main(void)
{  
  Tree* A[50];

  cout << ">> Règles d'une grammaire :" << endl;
  gen_forest(A);
  for (int i = 0; i < 5; ++i)
  {
     cout << "A[" << i << "] :" << endl;
     cout << A[i]->toString(0) << endl;
     cout << "\n\n" << endl; 
  }



  cout << ">> Règles de G0 :" << endl;
  g0_analyse("gpl.txt", A);
  for (int i = 5; i < 10; ++i)
  {
     cout << "A[" << i << "] :" << endl;
     cout << A[i]->toString(0) << endl;
     cout << "\n\n" << endl; 
  }


  return 0;
}