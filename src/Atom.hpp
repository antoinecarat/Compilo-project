/**
 * @file Atom.hpp
 * @author M.Cherrueau & A.Carat
 * @since 26/01/2017
 * @brief Atom node definition
 *
**/
#ifndef __ATOM_HPP__
#define __ATOM_HPP__

#include <string>

class Atom : Node
{
    public :
    	Atom(string code, int action, bool terminal);
    	~Atom();
		void print_node();

	private:
		string code;
    	int action;
    	bool terminal;
};

#endif //__ATOM_HPP__