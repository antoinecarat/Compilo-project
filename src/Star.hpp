/**
 * @file Star.hpp
 * @author M.Cherrueau & A.Carat
 * @since 26/01/2017
 * @brief Star node definition
 *
**/
#ifndef __STAR_HPP__
#define __STAR_HPP__

#include <iostream>

#include "Node.hpp"
#include "Tree.hpp"
using namespace std;

class Star : public Node
{
	public :
		Star(Tree* elt);
		~Star();
		Tree* getElt();
		string toString(int depth);

	private :
		Tree* elt;
};

#endif //__STAR_HPP__