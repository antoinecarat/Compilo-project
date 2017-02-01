#include "Atom.hpp"

Atom::Atom(std::string code, int action, bool terminal){
	this->code = code;
	this->action = action;
	this->terminal = terminal;
}

Atom::~Atom(){

}
string Atom::getCode(){
	return this->code;
}

int Atom::getAction(){
	return this->action;
}

bool Atom::getTerminal(){
	return this->terminal;
}

string Atom::toString(int depth){
	string act = to_string(this->action);
	string term = this->terminal ? "TERMINAL" : "NON-TERMINAL";
	return "---> Atom : " + this->code + " ; " + act + " ; " + term;
}