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
#include "BUILD.H"

using namespace std;

ostream& operator<< (ostream& stream, const Tab& tab) {
	for (int i = tab._tab; i > 0; i--) {
		stream << '\t';
	}
	return stream;
}

Expr_tree& parse_to_Expr_tree_recursive(list_Token::const_iterator* iter_pointer, const list_Token::const_iterator end) {
	debug_detail("parse_to_Expr_tree_recursive( " << (***iter_pointer).to_string() << " )\n");
	
	using namespace expr_tree;
	list_Token::const_iterator& iter = *iter_pointer;
	
	Expr_tree* tree = new Expr_tree( new Node(0) );
	
	//Expression* current = tree->expr(); // a strange trouble with 'const'
	Expression* current = (Expression*) tree->expr();
	
	for(; iter != end; iter++){
		// want a switch here; problem with ' tipeid'
		const Token* tok = *iter;
		const string name = tok->name();
		
		if 	  ( name == "Num"){
			const token::Num* item = (token::Num*) tok;
			current->set_link( new Num( item->value() ));
			
		} else if ( name == "+"){
			debug_detail("parsing Pluss[+] \n");
			
			Plus* plus = new Plus( current->get_link(), 0 );
			current->set_link( plus );
			
			debug_heavy(tree->to_string()); 
			
			current = plus;
			
		} // use recursion !!!
		else if ( name == "Brack_L"){
			debug_detail("parsing Brack_L \n");
			iter++;
			
			Node* node = new Node( 0 );
			current->set_link( node );
			
			debug_heavy(tree->to_string());
			
			node -> set_link( (expr_tree::Expression*)
					  parse_to_Expr_tree_recursive( &iter, end ).expr() 
					);
			if(end == iter) break;
			
		} else if ( name == "Brack_R"){
			debug_detail("parsing Brack_R \n");
			return *tree;
		} else {
			// may be an exeption
			cerr << "Unknow token '" << name << "'\n";
		}
	}
	
	return *tree;
}

namespace expr_tree { // Expr_tree& parse_to_Expr_tree(list_Token&)
	
Expr_tree& parse_to_Expr_tree(list_Token& lst) {
	list_Token::const_iterator iter = lst.begin();
	return parse_to_Expr_tree_recursive(&iter, lst.end());
}

}// namespace expt_tree

namespace expr_tree { // string to_string(int)
	
string Expression::to_string(int tab) const {
	ostringstream str;
	str << Tab(tab) << "Expression(" << _name << ")\n";
	return str.str();
}

string Expr_tree::to_string() const {
	ostringstream str;
	str << "Expr_tree((" << '\n'
	    << ((_expr)? _expr->to_string(1) : "\tnull\n") 
	    << "))\n";
	return str.str();
}

string Node::to_string(int tab) const {
	ostringstream str;
	
	str << Tab(tab) << "Node(\n";
	
	if (_link) { str << _link->to_string(tab + 1);}
	else 	   { str << Tab(tab + 1) << "null\n"; }
	
	str << Tab(tab) << ")\n";
	return str.str();
}
		
string Num::to_string(int tab) const {
	ostringstream str;
	str << Tab(tab) << "Num(" << _value << ")\n";
	return str.str();
}

string B_Oper::to_string(int tab) const {
	ostringstream str;
	
	str << Tab(tab) << "B-Oper{" << '\n';
	
	if (_left) { str << _left->to_string(tab + 1);}
	else 	   { str << Tab(tab + 1) << "null\n"; }
	
	str << Tab(tab + 1) << "__" << name() << "__" << "\n";
	
	if (_right) { str << _right->to_string(tab + 1);}
	else 	    { str << Tab(tab + 1) << "null\n"; }
	
	str << Tab(tab) << "}\n";
	
	return str.str();
}

}// namespace expt_tree
