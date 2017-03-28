#include "Lexical_unit.hpp"

Lexical_unit::Lexical_unit(string unit, bool term){
	this->unit = unit;
	this->term = term;
	this->action = 0;
}

Lexical_unit::Lexical_unit(string unit, bool term, int action){
	this->unit = unit;
	this->term = term;
	this->action = action;
}

Lexical_unit::~Lexical_unit(){

}

string Lexical_unit::toString()
{
    string res = "unit : ";
    res += unit + " ; ";
    res += term ? "TERM ; " : "NTERM ; ";
    res += action;
    return res;
}