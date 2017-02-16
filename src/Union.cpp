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

string Union::toString(int depth)
{
	string branchLeft = "---";
	string branchRight = "---"; 	

	for(int i=0; i<depth; i++) {
		branchLeft += "---";
		branchRight += "---";
	}
    return "---> Union \n" + branchLeft + this->left->toString(depth + 1) + "\n" + branchRight + this->right->toString(depth + 1);
}