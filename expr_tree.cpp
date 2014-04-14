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

ostream& operator<< (ostream& stream, const Tab& tab) {
	for (int i = tab._tab; i > 0; i--) {
		stream << '\t';
	}
	return stream;
}

namespace expr_tree { // Expr_tree& parse_to_Expr_tree(list_Token&)
	
Expr_tree& parse_to_Expr_tree(list_Token& lst) {
	using namespace expr_tree;
	
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
			Plus* plus = new Plus( current->get_link(), 0 );
			current->set_link( plus );
			current = plus;
			
		} // use recursion !!!
		/* else if ( name == "Brack_L"){
			Node* node = new Node( 0 );
			current->set_link( node );
			current = node;
			
		} else if ( name == "Brack_R"){
			//const token::Brack_L* item = (token::Brack_L*) tok; // unnecessary
			//Node* node = new Node( 0 );
			// go up
			current->set_link( node );
			current = node;
			
		} */ else {
			// may be an exeption
			cerr << "Unknow token '" << name << "'\n";
		}
	}
	
	return *tree;
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
