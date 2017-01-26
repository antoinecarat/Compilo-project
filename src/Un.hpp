/**
 * @file Un.hpp
 * @author M.Cherrueau & A.Carat
 * @since 26/01/2017
 * @brief Un node definition
 *
**/
#ifndef __UN_HPP__
#define __UN_HPP__

class Un : Node
{
	public :
		Un(Tree* elt);
		~Un();
		void print_node();
	private :
		Tree* elt;
};

#endif //__UN_HPP__