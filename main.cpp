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
//char str1[] = "  123 +100 +  400  ";
//char str1[] = "  123 +100 + 0 + 400 + 0 ";
char str1[] = "  123 +100 + 0 + 400 + 0 + 0 + 0 + ";
//char str1[] = "  123 +100 +  0 +  ";
//char str1[] = "  123 +100 +  400 + ";
//char str1[] = "    ";

 
// TODO: extract Printrable
// TODO: mem leak: list_Token, Expr_tree
////////////////////////////////////////////////////////////////////////
int main(){
	
	std::cout << "'" << str1 << "'\n\n";
	
	list_Token list_of_Tokens = token::parse_to_Token_list(str1);
	cout << list_of_Tokens;
	
	Expr_tree tree_of_Expr = expr_tree::parse_to_Expr_tree(list_of_Tokens);
	cout << tree_of_Expr.to_string() << '\n';
	
	tree_of_Expr.optimize();
	cout << tree_of_Expr.to_string() << '\n';
	
	return 0;
}
////////////////////////////////////////////////////////////////////////
/*
Expr_tree& parse_to_Expr_tree(list_Token& lst) {
	using namespace expr_tree;
	
	//Expr_tree* tree = new Expr_tree( new Node() );
	Expr_tree* tree = new Expr_tree( new Node(0) );
	
	//Expression* current = tree->expr(); // a strange trouble with 'const'
	Expression* current = (Expression*) tree->expr();
	
	for(list_Token::const_iterator iter = lst.begin();
			iter != lst.end();
			iter++){
		// want a switch here; problem with ' tipeid'
		const Token* tok = *iter;
		const string name = tok->name();
		
		if 	  ( name == "Num"){
			const token::Num* item = (token::Num*) tok;
			current->set_link( new Num( item->value() ));
			
		} else if ( name == "+"){
			const token::Plus* item = (token::Plus*) tok; // unnecessary
			Plus* plus = new Plus( current->get_link(), 0 );
			current->set_link( plus );
			current = plus;
			
		} else {
			// may be an exeption
			cerr << "Unknow token '" << name << "'\n";
		}
	}
	
	return *tree;
} */

