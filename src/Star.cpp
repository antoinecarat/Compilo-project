#include "Star.hpp"

Star::Star(Tree* elt){
	this->elt = elt;
}

Star::~Star(){

}

Tree* Star::getLeft(){return NULL;}
Tree* Star::getRight(){return NULL;}

Tree* Star::getElt(){
	return this->elt;
}

bool Star::getTerminal(){return NULL;}

string Star::getCode(){return NULL;}

int Star::getAction(){return NULL;}

string Star::toString(int depth)
{
	string branch = "---";

	for(int i=0; i<depth; i++) {
		branch += "---";
	}

    return "---> Star \n" + branch + this->elt->toString(depth + 1);
}


string Star::getType()
{
	return "Star";
}