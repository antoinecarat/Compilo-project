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

void print_forest()
{
  Tree* forest[5];
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

  for (int i = 0; i < 5; ++i)
  {
    cout << "A[" << i << "] :" << endl;
    cout << forest[i]->toString(0) << endl;
    cout << "++++++++++++++++++++++++++++++" << endl; 
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


  for (int i = 0; i < symbolsTable.size(); ++i)
  {
    if (unit.compare(symbolsTable.at(i)) == 0)
    {
      //cout << unit << " - SYMBOL" << endl;
      return true;
    }
  }
  //cout << unit << " - NOT SYMBOL" << endl;
  return false;
}

vector<Lexical_unit*> g0_scan(string filename) {

  ifstream file(filename, ios::in);
  vector<Lexical_unit*> lex_units;

  if(file){
    string unit;
    while(file >> unit)
    {
      int cmp=0;
      while (unit.length() > 1 && cmp < unit.length())
      {
        cmp=0; 
        char char1, char2;
        //TODO: gérer les doubles symboles
        //TODO: gérer les actions
        string lex_unit = "";
        lex_unit += unit.at(0);
        
        if (is_symbol(lex_unit))
        { 
          if(is_symbol(lex_unit+unit.at(1)))
          {
            lex_unit += unit.at(1);
          }
          lex_units.push_back(new Lexical_unit(lex_unit, 2));
          cout << "add : " << lex_unit << endl;
        } else if (lex_unit.compare("'") == 0)
        {
          string tmp = "";
          tmp += unit.at(++cmp);
          while(tmp.compare("'") != 0 && !is_symbol(tmp))
          {
            lex_unit += tmp;
            tmp = "";
            tmp += unit.at(++cmp);
          }
          if (tmp.compare("'") == 0)
          {
            lex_unit += tmp;
          }
          cout << "add : " << lex_unit << endl;
          lex_units.push_back(new Lexical_unit(lex_unit, 1));
        } else {
          string tmp = "";
          tmp += unit.at(++cmp);
          while(!is_symbol(tmp))
          {
            lex_unit += tmp;
            tmp = "";
            tmp += unit.at(++cmp);
          }
          cout << "add : " << lex_unit << endl;
          cout << "add : " << tmp << endl;
          lex_units.push_back(new Lexical_unit(lex_unit, 0));
          lex_units.push_back(new Lexical_unit(tmp, 2));
        }
        ++cmp;
      //sinon si le premeir caractère est un " # "
      // - on prends les caractères suivants tant que se sont des chiffres.
      // - new Lexical_unit(unit, 3);
      //sinon si le premeir caractère est un " ' "
      // - on regarde les caractères suivants jusqu'au prochain " ' ".
      // - new Lexical_unit(unit, 0);
      //sinon
      // - on regarde les caractères suivants jusqu'au prochain symbole/séparateur.
      // - new Lexical_unit(unit, 1);
      unit = unit.substr(cmp);
      }
    }

    file.close();

  }
  else {
    cerr << "Impossible d'ouvrir le fichier !" << endl;
  }

  return lex_units;
}

void g0_analyse(string filename)
{
  //Appelle le scan, et execute les actions.
}


int main(void)
{

  /*Tree* t_left = new Tree(new Atom("FLECHE", 0, true));
  Tree* t_star = new Tree(new Atom("N", 0, false));
  Tree* t_union_left = new Tree(new Atom("T", 0, false));
  Tree* t_union_right = new Tree(new Star(t_star));
  Tree* t_right = new Tree(new Union(t_union_left, t_union_right));
  Tree* t = new Tree(new Conc(t_left, t_right));

  cout << t->toString(0) << endl;*/

  //print_forest();

  g0_scan("gpl.txt");

  return 0;
}