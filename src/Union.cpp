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

Tree* Union::getElt(){return NULL;}

bool Union::getTerminal(){return NULL;}

string Union::getCode(){return NULL;}

int Union::getAction(){return NULL;}

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

string Union::getType()
{
	return "Union";
}