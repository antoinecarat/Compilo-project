/**
 * @file Lexical_unit.hpp
 * @author M.Cherrueau & A.Carat
 * @since 16/02/2017
 * @brief Lexical unit definition
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
		int type;
	public :
		Lexical_unit(string unit, int type);
		~Lexical_unit();
		string toString();
};

#endif //__LEXICALUNIT_HPP__