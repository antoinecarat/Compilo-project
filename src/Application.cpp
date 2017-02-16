#include "Tree.hpp"
#include "Node.hpp"
#include "Atom.hpp"
#include "Conc.hpp"
#include "Union.hpp"
#include "Star.hpp"
#include "Un.hpp"

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

bool isSymbol(string unit){
  vector<string> symbolsTable;
  symbolsTable.push_back(";");

  for (int i = 0; i < symbolsTable.size(); ++i)
  {
    if (symbolsTable.at(i) == unit)
    {
      return true;
    }
  }

  return false;

  /*switch(unit) {
    case ";" :
      return true;
    case "+" :
      return true;
    case "-" :
      return true;
    case "*" :
      return true;
    case "?" :
      return true;
    case ":" :
      return true;
    case "=" :
      return true;
    case "(" :
      return true;
    case ")" :
      return true;
    case "[" :
      return true;
    case "]" :
      return true;
    case "{" :
      return true;
    case "}" :
      return true;
    case "&" :
      return true;
    case "|" :
      return true;
    case "==" :
      return true;
    case "&&" :
      return true;
    case "||" :
      return true;
    case "<<" :
      return true;
    case ">>" :
      return true;
    case "<=" :
      return true;
    case ">=" : 
  	  return true;
    default :
      return false;
  }*/
}

/*bool isNum(string unit){
  regex e ("^-?\\d+");
  return (regex_match (unit,e));
}*/

bool is_symbol(string unit)
{
  return false;
}

//ajouter un pointeur sur l'emplacement précédent
//pour ne pas 
Lexical_unit* g0_scan(string filename) {

  ifstream file(filename, ios::in);
  Lexical_unit* lex_unit;

  if(file){
    string unit;
    file >> unit;

    //decouper pour prendre le premier
    //si le premier caractère est un symbole
    // - si on peut former un double symbole avec le caractère suivant
    //   - unit = char1+char2; new Lexical_unit(unit, 2);
    //sinon si le premeir caractère est un " # "
    // - on prends les caractères suivants tant que se sont des chiffres.
    // - new Lexical_unit(unit, 3);
    //sinon si le premeir caractère est un " ' "
    // - on regarde les caractères suivants jusqu'au prochain " ' ".
    // - new Lexical_unit(unit, 0);
    //sinon
    // - on regarde les caractères suivants jusqu'au prochain symbole/séparateur.
    // - new Lexical_unit(unit, 1);

    file.close();

  }
  else {
    cerr << "Impossible d'ouvrir le fichier !" << endl;
  }

  return lex_unit;
}

void g0_analyse(string filename)
{
  //Appelle le scan, et les actions.
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

  g0_analyse("gpl.txt");

  return 0;
}