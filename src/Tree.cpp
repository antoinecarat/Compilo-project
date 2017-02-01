#include "Tree.hpp"

Tree::Tree(Node* root)
{
	this->root = root;
}

Tree::~Tree()
{

}

Node* Tree::getRoot()
{
 return Tree::root;
}

void Tree::setRoot(Node* root)
{
	this->root = root;
}

string Tree::toString(int depth)
{
    return this->root->toString(depth);
}