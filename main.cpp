/** main.cpp
 * 
 * This is the main file of a trainig project 'Parser-Tree'.
 * It's gonna be writen in the best C++.
 * This file is needed for final interaction with the user
 * and for quick testing of new code.
 * 
 * Files:
 * main.cpp		run the progream (interface)
 * test.cpp		runs all tests
 * token.hpp
 * expr-tree.hpp
 * 
 * Program functionality:
 *   *To parse strings of:
 *     1) numbers:
 *         100, -23
 *     2) b-operators:
 *         +, -, *
 *     3) brackets:
 *         ()
 *     4) variables:
 *         x, y, z
 *     5) u-operaors:
 *         -(23), difx(x*x + y)
 *   *To calculate constant expressions
 *   *To print var-expressions
 * */

#include <stdio.h>
#include <iostream>
#include <string>
#include <list>

#include "token.hpp"
#include "expr-tree.hpp"
#include "utils.hpp"

using namespace std;
using namespace Utils_space; // how do i call spaces?  

typedef Token_space::Token Token;
typedef Expr_Tree_space::Expression Expression;
//----------------------------------------------------------------------

char str1[] = "  123 +100 + (   400+)  ";
list<Token> parse_to_Token_list(string str);

////////////////////////////////////////////////////////////////////////
int main(){
	
	std::cout << "'" << str1 << "'\n";
	
	list<Token> list_of_Tokens = Token_space::parse_to_Token_list(str1);
	cout << list_of_Tokens;
	
	
	return 0;
}
////////////////////////////////////////////////////////////////////////

/*

const char* parse_space(const char* pointer, list<Token>& lst){  // const ???
	while(' ' == *pointer)
		pointer += 1;
	return pointer;
}

list<Token> parse_to_Token_list(string str){
	using namespace Token_space;
	typedef const char* (*Parse_function)(const char*, list<Token>&);
	
	list<Parse_function> parse_func_list;
	parse_func_list << Num::parse 
			<< Plus::parse
			<< Brack_L::parse
			<< Brack_R::parse;
	parse_func_list.push_front(parse_space);
	//--------------------------------------------------------------
	list<Token> lst;
	
	const char* pointer  = &str[0];
	
	list<Parse_function>::const_iterator iter_func = parse_func_list.begin();
	while('\0' != *pointer){
		pointer = (*iter_func)(pointer, lst);
		iter_func++;
		if(parse_func_list.end() == iter_func)
			iter_func = parse_func_list.begin();
	}
	
	return lst;
}

*/
