#include "Star.hpp"

Star::Star(Tree* elt){
	this->elt = elt;
}

Star::~Star(){

}

Tree* Star::getElt(){
	return this->elt;
}

string Star::toString(int depth)
{
	string branch = "---";

	for(int i=0; i<depth; i++) {
		branch += "---";
	}

    return "---> Star \n" + branch + this->elt->toString(depth + 1) + "\n";
}