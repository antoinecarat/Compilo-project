#include "Conc.hpp"

Conc::Conc(Tree* left, Tree* right){
	this->left = left;
	this->right = right;
}

Conc::~Conc(){

}

Tree* Conc::getLeft(){
	return this->left;
}

Tree* Conc::getRight(){
	return this->right;
}

string Conc::toString()
{
    return "---> Conc \n ---" + this->left->toString() + "\n ---" + this->right->toString();
}