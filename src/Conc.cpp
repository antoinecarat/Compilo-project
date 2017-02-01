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

string Conc::toString(int depth)
{
	string branchLeft = "---";
	string branchRight = "---"; 	

	for(int i=0; i<depth; i++) {
		branchLeft += "---";
		branchRight += "---";
	}

    return "---> Conc \n" + branchLeft + this->left->toString(depth + 1) + "\n" + branchRight + this->right->toString(depth + 1);
}