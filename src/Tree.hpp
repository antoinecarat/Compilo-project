/**
 * @file Tree.hpp
 * @author M.Cherrueau & A.Carat
 * @since 19/01/2017
 * @brief Generic tree definition
 *
**/
#ifndef __TREE_HPP__
#define __TREE_HPP__

#include <iostream>

class Node;

using namespace std;

class Tree
{
    public:
        Tree(Node* root);
        ~Tree();
        Node* getRoot();
        void setRoot(Node* root);
        void print_tree();
		string toString(int depth);

    private:
        Node *root;
};

#include "Node.hpp"

#endif //__TREE_HPP__