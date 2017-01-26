/**
 * @file Un.hpp
 * @author M.Cherrueau & A.Carat
 * @since 26/01/2017
 * @brief Un node definition
 *
**/
#ifndef __UN_HPP__
#define __UN_HPP__

#include <iostream>

#include "Node.hpp"
#include "Tree.hpp"
using namespace std;

class Un : public Node
{
	public :
		Un(Tree* elt);
		~Un();
		Tree* getElt();
		string toString();


	private :
		Tree* elt;
};

#endif //__UN_HPP__