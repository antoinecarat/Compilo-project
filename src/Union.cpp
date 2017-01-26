#include "Union.hpp"

Union::Union(Tree* left, Tree* right){
	this->left = left;
	this->right = right;
}

Union::~Union(){

}

Tree* Union::getLeft(){
	return this->left;
}

Tree* Union::getRight(){
	return this->right;
}

string Union::toString()
{
    return "---> Union \n ---" + this->left->toString() + "\n ---" + this->right->toString() + "\n";
}