#include "Lexical_unit.hpp"

Lexical_unit::Lexical_unit(string unit, string code, bool term){
	this->unit = unit;
	this->code = code;
	this->term = term;
	this->action = 0;
}

Lexical_unit::Lexical_unit(string unit, string code, bool term, int action){
	this->unit = unit;
	this->code = code;
	this->term = term;
	this->action = action;
}

Lexical_unit::~Lexical_unit(){

}

string Lexical_unit::getUnit()
{
	return this->unit;
}

int Lexical_unit::getAction()
{
	return this->action;
}

string Lexical_unit::toString()
{
    string res = "unit : ";
    res += unit + " ; ";
    res += code + " ; ";
    res += term ? "TERM ; " : "NTERM ; ";
    res += to_string(action);
    return res;
}