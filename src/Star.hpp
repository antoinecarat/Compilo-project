/**
 * @file Star.hpp
 * @author M.Cherrueau & A.Carat
 * @since 26/01/2017
 * @brief Star node definition
 *
**/
#ifndef __STAR_HPP__
#define __STAR_HPP__

class Star : Node
{
	public :
		Star(Tree* elt);
		~Star();
		void print_node();
	private :
		Tree* elt;
};

#endif //__STAR_HPP__