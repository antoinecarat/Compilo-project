#include "Tree.hpp"
#include "Node.hpp"
#include "Atom.hpp"
#include "Conc.hpp"
#include "Union.hpp"
#include "Star.hpp"
#include "Un.hpp"

#include <iostream>

int main(void) {

   Tree* t = new Tree();
   Tree* t_left = new Tree();
   Tree* t_right = new Tree();
   Tree* t_star = new Tree();
   Tree* t_union_left = new Tree();
   Tree* t_union_right = new Tree();

   t_left->setRoot(new Atom("FLECHE", 0, true));
   t_union_left->setRoot(new Atom("T", 0, false));
   t_star->setRoot(new Atom("N", 0, false));
   t_union_right->setRoot(new Star(t_star));
   t_right->setRoot(new Union(t_union_left, t_union_right));


   Node* root = new Conc(t_left, t_right);
   t->setRoot(root);

   cout << t->toString() << endl;

   return 0;
}