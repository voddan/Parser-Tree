/** utils.hpp
 * 
 * Util functions 
 * for i/o and dump
 * 
 * */ 

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <iostream>
#include <string>
#include <list>

#include "token.hpp"
#include "expr-tree.hpp"

using namespace std;

typedef Token_space::Token Token;
typedef Expr_Tree_space::Expression Expression;
//----------------------------------------------------------------------

namespace Utils_space{ // namespace Utils_space
	
ostream& operator<<(ostream& str, const Expression& expr) {
	str << expr.to_string(); 
	return str;
}

ostream& operator<<(ostream& str, const Token& token) {
	str << token.to_string(); 
	return str;
}
	
ostream& operator<<(ostream& str, list<Token*> lst) { // conflict with list - list
	cout << "list<Token>[ ";
	for(list<Token*>::const_iterator iter = lst.begin();
			iter != lst.end(); 
			iter++){
		//cout << *iter << " ";
		cout << "             " << (**iter).to_string() << '\n';
	}
	cout << "]\n";
	return str;
}

template<typename T> 
list<T>& operator<<(
		list<T>& lst, 
		typename list<T>::value_type item) {
	lst.push_back(item);
	return lst;
}


} // namespace Utils_space

#endif // _UTILS_HPP_
