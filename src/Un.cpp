#include "Un.hpp"

Un::Un(Tree* elt){
	this->elt = elt;
}

Un::~Un(){

}

Tree* Un::getLeft(){return NULL;}
Tree* Un::getRight(){return NULL;}

Tree* Un::getElt(){
	return this->elt;
}

bool Un::getTerminal(){return NULL;}

string Un::getCode(){return NULL;}

int Un::getAction(){return NULL;}

string Un::toString(int depth)
{
	string branch = "---";

	for(int i=0; i<depth; i++) {
		branch += "---";
	}

    return "---> Un \n" + branch + this->elt->toString(depth +1);
}

string Un::getType()
{
	return "Un";
}