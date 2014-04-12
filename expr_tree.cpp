/** expr_tree.cpp
 * 
 * Implementation of Expressions
 * 
 * Expr_tree& parse_to_Expr_tree(list_Token& lst);
 * */ 
 
#include <string>
#include <algorithm>
#include <sstream>
#include <list>

#include <cctype>
#include <assert.h> 

#include "expr_tree.hpp"
#include "token.hpp"

using namespace std;
//using namespace expr_tree; //?


namespace expr_tree {
	
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
			//const token::Plus* item = (token::Plus*) tok; // unnecessary
			Plus* plus = new Plus( current->get_link(), 0 );
			current->set_link( plus );
			current = plus;
			
		} else {
			// may be an exeption
			cerr << "Unknow token '" << name << "'\n";
		}
	}
	
	return *tree;
}

}// namespace expt_tree
