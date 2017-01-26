#include "Tree.hpp"

Tree::Tree()
{

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

string Tree::toString()
{
    return this->root->toString();
}