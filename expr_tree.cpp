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

#include "parsing_common.hpp"
#include "expr_tree.hpp"
#include "BUILD.H"


using namespace std;

// where should I place private helper classes like this?
//typedef std::ostream ostream;
class Tab {
	public:
		Tab(int tab): _tab(tab) {}
		friend std::ostream& operator<< (std::ostream& stream, const Tab& tab);
	private:
		const int _tab;
};

ostream& operator<< (ostream& stream, const Tab& tab) {
	for (int i = tab._tab; i > 0; i--) {
		stream << '\t';
	}
	return stream;
}
//----------------------------------------------------------------------

/*
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
			iter--; // because of the for() loop
			
		} else if ( name == "Brack_R"){
			debug_detail("parsing Brack_R \n");
			iter++;
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
*/

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


namespace expr_tree { // Expression* optimize()
	
Expression* Node::optimize() { 
	if(_link) _link = _link->optimize();
	// should I do like this?
	
	return this;  // debug
	/*
	Expression* t = _link;
	delete this;
	return t; // */
}

Expression* B_Oper::optimize() { 
	if(_left)  _left  = _left->optimize();
	if(_right) _right = _right->optimize();
	
	// pay attention
	if(_left && _right &&
	   _left ->name() == "Num" &&
	   _right->name() == "Num") {
		// strange bug
		debug("optimize B_Oper(left is Num, right is Num)\n");
		Num* t = new Num( calculate(
					((Num*) _left )->value(),
					((Num*) _right)->value() ) 
				); 
		delete this; 
		return t; 
	}
	
	return this;
}

Expression* Plus::optimize() { 
	Expression* t = B_Oper::optimize(); // important !!
	if(this != t) return t;
	
	if(get_left() &&
	   get_left()->name() == "Num" &&
	   ((Num*) get_left())->value() == 0) {
		// strange bug
		debug("optimize B_Oper[+](left is Num, left == 0)\n");
		Expression* t = get_right();
		//delete this; 
		return t; 
	}
	
	if(get_right() &&
	   get_right()->name() == "Num" &&
	   ((Num*) get_right())->value() == 0) {
		// strange bug
		debug("optimize B_Oper[+](right is Num, right == 0)\n");
		Expression* t = get_left();
		//delete this; 
		return t; 
	}
	
	return this;
}
		
} // namespace expr_tree
