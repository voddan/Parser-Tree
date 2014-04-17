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
////////////////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////////////////
