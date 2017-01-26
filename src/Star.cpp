#include "Star.hpp"

Star::Star(Tree* elt){
	this->elt = elt;
}

Star::~Star(){

}

Tree* Star::getElt(){
	return this->elt;
}

string Star::toString()
{
    return "---> Star \n ---" + this->elt->toString() + "\n";
}