/**
 * @file Conc.hpp
 * @author M.Cherrueau & A.Carat
 * @since 26/01/2017
 * @brief Concatenation node definition
 *
**/
#ifndef __CONC_HPP__
#define __CONC_HPP__

#include <iostream>

#include "Node.hpp"
#include "Tree.hpp"
using namespace std;

class Conc : public Node
{
	public :
		Conc(Tree* left, Tree* right);
		~Conc();
		Tree* getLeft();
		Tree* getRight();
		Tree* getElt();
		bool getTerminal();
		string getCode();
		int getAction();
		string toString(int depth);
		string getType();
	private : 
		Tree* left;
		Tree* right;

};

#endif //__CONC_HPP__