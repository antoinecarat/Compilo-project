/**
 * @file Tree.hpp
 * @author M.Cherrueau & A.Carat
 * @since 19/01/2017
 * @brief Generic tree definition
 *
**/
#ifndef __TREE_HPP__
#define __TREE_HPP__

class Tree
{
    public:
        Tree();
        ~Tree();
        void print_tree();

    private:
        node *root;
};
#endif //__TREE_HPP__