#include "Tree.hpp"
#include "Node.hpp"
#include "Atom.hpp"
#include "Conc.hpp"
#include "Union.hpp"
#include "Star.hpp"
#include "Un.hpp"

#include <iostream>

Tree* genConc(Tree* left, Tree* right)
{
   return new Tree(new Conc(left, right));
}

Tree* genUnion(Tree* left, Tree* right)
{
   return new Tree(new Union(left, right));
}

Tree* genStar(Tree* star)
{
   return new Tree(new Star(star));
}

Tree* genUn(Tree* un)
{
   return new Tree(new Un(un));
}

Tree* genAtom(std::string code, int action, bool terminal)
{
   return new Tree(new Atom(code, action, terminal));
}

void print_forest()
{
   Tree* forest[5];
   forest[0] = genConc(genStar(genConc(genConc(genConc(genAtom("N", 0, false),
                                                       genAtom("F", 0, false)
                                                       ),
                                               genAtom("E", 0, false)
                                               ),
                                       genAtom(",", 1, true)
                                       )),
                        genAtom(";", 1, true)
                        );
   forest[1] = genAtom("I", 0, false);
   forest[2] = genConc(genAtom("I", 0, false),
                       genStar(genConc(genAtom("+", 0, true),
                                       genAtom("T", 0, false)
                                      ))
                      );
   forest[3] = genConc(genAtom("F", 0, false),
                       genStar(genConc(genAtom(".", 1, true),
                                       genAtom("F", 0, false)
                                       ))
                       );
   forest[4] = genUnion(genAtom("IDNTER", 0, false),
                        genUnion(genAtom("ELTER", 0, false),
                                 genUnion(genConc(genConc(genAtom("(", 0, true),
                                                          genAtom("E", 0, false)
                                                          ),
                                                  genAtom(")", 0, true)
                                                  ),
                                          genUnion(genConc(genConc(genAtom("[", 0, true),
                                                                   genAtom("E", 0, false)
                                                                  ),
                                                           genAtom("]", 0, true)
                                                          ),
                                                   genConc(genConc(genAtom("(\\", 0, true),
                                                                   genAtom("E", 0, false)
                                                                  ),
                                                           genAtom("\\)", 0, true)
                                                          )
                                                   )
                                          )
                                 )
                        );

   for (int i = 0; i < 5; ++i)
   {
      cout << "A[" << i << "] :" << endl;
      cout << forest[i]->toString(0) << endl;
      cout << "------------------------------" << endl; 
   }

}

int main(void) {

   /*Tree* t_left = new Tree(new Atom("FLECHE", 0, true));
   Tree* t_star = new Tree(new Atom("N", 0, false));
   Tree* t_union_left = new Tree(new Atom("T", 0, false));
   Tree* t_union_right = new Tree(new Star(t_star));
   Tree* t_right = new Tree(new Union(t_union_left, t_union_right));
   Tree* t = new Tree(new Conc(t_left, t_right));

   cout << t->toString(0) << endl;*/

   print_forest();

   return 0;
}