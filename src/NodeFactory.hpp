/**
 * @file NodeFactory.hpp
 * @author M.Cherrueau & A.Carat
 * @since 19/01/2017
 * @brief Node factory definition
 *
**/
#ifndef __NODEFACTORY_HPP__
#define __NODEFACTORY_HPP__

class NodeFactory
{
    public:
        NodeFactory();
        ~NodeFactory();
        void create(string name);

};

#endif //__NODEFACTORY_HPP__