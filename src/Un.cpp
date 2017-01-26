#include "Un.hpp"

Un::Un(Tree* elt){
	this->elt = elt;
}

Un::~Un(){

}

Tree* Un::getElt(){
	return this->elt;
}

string Un::toString()
{
    return "---> Un \n ---" + this->elt->toString() + "\n";
}