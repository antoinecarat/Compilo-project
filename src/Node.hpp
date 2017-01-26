/**
 * @file Node.hpp
 * @author M.Cherrueau & A.Carat
 * @since 19/01/2017
 * @brief Generic node definition
 *
**/
#ifndef __NODE_HPP__
#define __NODE_HPP__

union Node
{
    Atom atom;
    Conc conc;
    Union uni;
    Star star;
    Un un;
};

#endif //__NODE_HPP__