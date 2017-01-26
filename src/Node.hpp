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

using namespace std;

class Node
{
	public :
		Node();
		virtual ~Node();
		virtual string toString() = 0;
};

#endif //__NODE_HPP__