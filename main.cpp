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

//#define DEBUG

#include "token.hpp"
#include "expr_tree.hpp"
#include "utils.hpp"

using namespace std;
using namespace utils;


//----------------------------------------------------------------------

//char str1[] = "  123 +100 + (   400+)  ";
char str1[] = "    ";


Expr_tree& parse_to_Expr_tree(list_Token& lst);
// TODO: extract Printrable
// TODO: mem leak: list_Token, Expr_tree
////////////////////////////////////////////////////////////////////////
int main(){
	
	std::cout << "'" << str1 << "'\n\n";
	
	list_Token list_of_Tokens = token::parse_to_Token_list(str1);
	cout << list_of_Tokens;
	
	Expr_tree tree_of_Expr = parse_to_Expr_tree(list_of_Tokens);
	cout << tree_of_Expr.to_string() << '\n';
	
	return 0;
}
////////////////////////////////////////////////////////////////////////

Expr_tree& parse_to_Expr_tree(list_Token& lst) {
	using namespace expr_tree;
	
	//Expr_tree* tree = new Expr_tree( new Node() );
	Expr_tree* tree = new Expr_tree( 0 );
	
	return *tree;
}

