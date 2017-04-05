/**
 * @file Lexical_unit.hpp
 * @author M.Cherrueau & A.Carat
 * @since 16/02/2017
 * @brief Lexical unit definition.
 *
**/
#ifndef __LEXICALUNIT_HPP__
#define __LEXICALUNIT_HPP__

#include <iostream>

using namespace std;

class Lexical_unit
{
	private : 
		string unit;
		string code;
		bool term;
		int action;
	public :
		Lexical_unit(string unit, string code, bool term, int action);
		Lexical_unit(string unit, string code, bool term);
		~Lexical_unit();
		string getUnit();
		string getCode();
		bool getTerminal();
		int getAction();
		string toString();
};

#endif //__LEXICALUNIT_HPP__