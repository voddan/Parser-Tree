/** expr_tree.hpp
 * 
 * Classes for expression trees
 * 
 * Expression
 *   Num
 *   B-Oper
 *     Plus
 * */ 

#ifndef _EXPR_TREE_HPP_
#define _EXPR_TREE_HPP_

#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>

#include "token.hpp"

using namespace std;
//----------------------------------------------------------------------
// where should I place private helper classes like this?
class Tab {
	public:
		Tab(int tab): _tab(tab) {}
		friend ostream& operator<< (ostream& stream, const Tab& tab);
	private:
		const int _tab;
};

ostream& operator<< (ostream& stream, const Tab& tab);

//----------------------------------------------------------------------
namespace expr_tree { // namespace expr_tree
	
class Expression{
	public:
		Expression(const string name) : _name(name) {}
		virtual ~Expression() {}
		const string name() const {return _name;}
		
		//---------------------------------
		virtual string to_string(int tab) const{
			ostringstream str;
			str << Tab(tab) << "Expression(" << _name << ")\n";
			return str.str();
		}
		
		virtual void set_link(Expression* link) = 0;
		virtual Expression* get_link() const 	= 0;
		
	private:
		const string _name;
};

class Expr_tree  { // not an Expression
	public:
		Expr_tree(Expression* expr) : _expr(expr) {}
		~Expr_tree() { 
			#ifdef DEBUG 
				std::cerr << "Expr_tree is out\n"; 
			#endif
			delete _expr; 
		}
		
		string to_string() const{
			ostringstream str;
			str << "Expr_tree((" << '\n'
			    << ((_expr)? _expr->to_string(1) : "\tnull\n") 
			    << "))\n";
			return str.str();
		}
		
		//const string name() const {return "Expr_tree";}
		
		const Expression* expr() const { return _expr; };
	
	private:
		const Expression* _expr;
		// Expression* _expr;
};
		
		
class Node: public Expression {
	public:
		Node(Expression* link = 0) : Expression("Node"), _link(link) {}
		virtual ~Node() { delete _link; }
		
		virtual string to_string(int tab) const{
			ostringstream str;
			
			str << Tab(tab) << "Node(\n";
			
			if (_link) { str << _link->to_string(tab + 1);}
			else 	   { str << Tab(tab + 1) << "null\n"; }
			
			str << Tab(tab) << ")\n";
			return str.str();
		}
		
		virtual void set_link(Expression* link) { _link = link; }
		virtual Expression* get_link() const 	{ return _link; }
	private:
		Expression* _link; // will children get this?
};



class Num: public Expression {
	public:
		Num(int value) : Expression("Num"), _value(value) {}
		
		string to_string(int tab) const{
			ostringstream str;
			str << Tab(tab) << "Num(" << _value << ")\n";
			return str.str();
		}
		
		virtual void set_link(Expression* link) {
			std::cerr << "Unsupported operation expr_tree::Num.set_link()\n";
		}
		virtual Expression* get_link() const {
			std::cerr << "Unsupported operation expr_tree::Num.get_link()\n";
			return 0;
		}
	private:
		const int _value;
};

//*
class B_Oper: public Expression{
	public:
		B_Oper(string name, Expression* left = 0, Expression* right = 0) : 
			Expression(name), _left(left), _right(right) {} // & vs *
		virtual ~B_Oper() {delete _left; delete _right;}
		
		string to_string(int tab) const{
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
		
		void set_left(Expression* left) { _left = left; }
		Expression* get_left() const 	{ return _left; }
		
		void set_right(Expression* right) { _right = right; }
		Expression* get_rightt() const 	  {  return _right; }
		
		virtual void set_link(Expression* link) { _right = link; }
		virtual Expression* get_link() const 	{ return _right; }
		
		//virtual int apply(int left, int right)
	private:
		Expression* _left;
		Expression* _right;
}; // */

class Plus : public B_Oper {
	public: 
		Plus(Expression* left = 0, Expression* right = 0) : B_Oper("+", left,  right) {}
};

} // namespace expr_tree
////////////////////////////////////////////////////////////////////////
namespace expr_tree {
	
Expr_tree& parse_to_Expr_tree(token::list_Token& lst);

} // namespace expr_tree
////////////////////////////////////////////////////////////////////////


typedef expr_tree::Expression Expression;
typedef expr_tree::Expr_tree Expr_tree;

#endif // _EXPR_TREE_HPP_
