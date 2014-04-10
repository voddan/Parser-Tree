/** main.cpp executable
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
 * expr_tree.hpp
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
#include "expr_tree.hpp"
#include "utils.hpp"

using namespace std;
using namespace utils; // how do i call spaces?  1

typedef token::Token Token;
typedef expr_tree::Expression Expression;
//----------------------------------------------------------------------

char str1[] = "  123 +100 + (   400+)  ";

////////////////////////////////////////////////////////////////////////
int main(){
	
	std::cout << "'" << str1 << "'\n\n";
	
	token::list_Token list_of_Tokens = token::parse_to_Token_list(str1);
	cout << list_of_Tokens;
	
	 /*
	for(token::list_Token::iterator iter = list_of_Tokens.begin();
			iter != list_of_Tokens.end();
			iter++) {
		delete *iter;
	} // */
	
	
	return 0;
}
////////////////////////////////////////////////////////////////////////

