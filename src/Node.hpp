/**
 * @file Node.hpp
 * @author M.Cherrueau & A.Carat
 * @since 19/01/2017
 * @brief Generic node definition
 *
**/
#ifndef __NODE_HPP__
#define __NODE_HPP__

class Node
{
	public :
		virtual Node();
		virtual ~Node();
		virtual void print_node() = 0;

};

#endif //__NODE_HPP__