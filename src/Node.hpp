/**
 * @file Node.hpp
 * @author M.Cherrueau & A.Carat
 * @since 19/01/2017
 * @brief Generic node definition
 *
**/
#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <Tree.hpp>
#include <vector>
#include <string>

class Node
{
    public:
        Node(string name);
        ~Node();
        void add_son(Tree *t);
        void print_node();

    private:
        string name;
        vector<Tree*> sons;
};

#endif //__NODE_HPP__