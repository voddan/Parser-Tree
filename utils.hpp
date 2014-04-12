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
#include "expr_tree.hpp"

using namespace std;

//----------------------------------------------------------------------

namespace utils{ // namespace utils
	
ostream& operator<<(ostream& str, const Expression& expr) {
	str << expr.to_string(); 
	return str;
}

ostream& operator<<(ostream& str, const Token& token) {
	str << token.to_string(); 
	return str;
}

ostream& operator<<(ostream& str, list<Token*>& lst) { // conflict with list - list
	cout << "list<Token>[ \n";
	for(list<Token*>::const_iterator iter = lst.begin();
			iter != lst.end(); 
			iter++){
		cout << "             " << (**iter) << '\n';
	}
	cout << "]\n";
	return str;
} 

/*
template<typename T> 
ostream& operator<<(ostream& str, list<T>& lst) {
	cout << "list<T>[ \n";
	for(list<T>::const_iterator iter = lst.begin();
			iter != lst.end(); 
			iter++){
		//cout << "             " << (**iter) << '\n';
		cout << (**iter) << " ";
	}
	cout << "]\n";
	return str;
} */

template<typename T> 
list<T>& operator<<(
		list<T>& lst, 
		typename list<T>::value_type item) {
	lst.push_back(item);
	return lst;
}


} // namespace utils

#endif // _UTILS_HPP_
