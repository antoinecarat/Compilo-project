#include "Lexical_unit.hpp"

Lexical_unit::Lexical_unit(string unit, int type){
	this->unit = unit;
	this->type = type;
}

Lexical_unit::~Lexical_unit(){

}

string Lexical_unit::toString()
{
    return "unit : " + unit + " ; type : " + " .\n";
}