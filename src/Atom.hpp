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
#include "Node.hpp"
using namespace std;

class Atom : public Node
{
    public :
    	Atom(std::string code, int action, bool terminal);
    	~Atom();
		string getCode();
		int getAction();
		bool getTerminal();
        string toString(int depth);
        string getType();

        Tree* getLeft();
        Tree* getRight();
        Tree* getElt();

	private:
		string code;
    	int action;
    	bool terminal;
};

#endif //__ATOM_HPP__