#include "Un.hpp"

Un::Un(Tree* elt){
	this->elt = elt;
}

Un::~Un(){

}

Tree* Un::getElt(){
	return this->elt;
}

string Un::toString(int depth)
{
	string branch = "---";

	for(int i=0; i<depth; i++) {
		branch += "---";
	}

    return "---> Un \n" + branch + this->elt->toString(depth +1) + "\n";
}