/**
 * @file Union.hpp
 * @author M.Cherrueau & A.Carat
 * @since 26/01/2017
 * @brief Union node definition
 *
**/
#ifndef __UNION_HPP__
#define __UNION_HPP__

#include <iostream>

#include "Node.hpp"
#include "Tree.hpp"
using namespace std;

class Union : public Node
{
	public :
		Union(Tree* left, Tree* right);
		~Union();
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

#endif //__UNION_HPP__