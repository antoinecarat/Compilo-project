/**
 * @file Node.hpp
 * @author M.Cherrueau & A.Carat
 * @since 19/01/2017
 * @brief Generic node definition
 *
**/
#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <iostream>
#include "Tree.hpp"

using namespace std;

class Node
{
	public :
		Node();
		virtual ~Node();
		virtual Tree* getLeft() = 0;
		virtual Tree* getRight() = 0;
		virtual Tree* getElt() = 0;
		virtual bool getTerminal() = 0;
		virtual string toString(int depth) = 0;
		virtual string getType() = 0;
};

#endif //__NODE_HPP__