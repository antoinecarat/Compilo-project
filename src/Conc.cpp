#include "Conc.hpp"

Conc::Conc(Tree* left, Tree* right)
{
	this->left = left;
	this->right = right;
}

Conc::~Conc()
{

}

Tree* Conc::getLeft()
{
	return this->left;
}

Tree* Conc::getRight()
{
	return this->right;
}

Tree* Conc::getElt(){return NULL;}

bool Conc::getTerminal(){return NULL;}

string Conc::getCode(){return NULL;}

int Conc::getAction(){return NULL;}

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

string Conc::getType()
{
	return "Conc";
}