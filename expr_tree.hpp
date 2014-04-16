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

#include <algorithm>
#include <sstream>
#include <string>

#include "BUILD.H"

typedef std::string string;

//----------------------------------------------------------------------
namespace expr_tree {
	
class Expression{ 
	public:
		Expression(const string name) : _name(name) {}
		virtual ~Expression() {}
		const string name() const {return _name;}
		virtual string to_string(int tab = 0) const; // see expr-tree.cpp 
		//---------------------------------
		virtual Expression* optimize() { return this; }
		
		virtual void set_link(Expression* link) = 0;
		virtual Expression* get_link() const 	= 0;
		
	private:
		const string _name;
};

class Expr_tree  { // not an Expression
	public:
		Expr_tree(Expression* expr) : _expr(expr) {}
		~Expr_tree() { 
			debug("Expr_tree is out\n"); 
			delete _expr; 
		}
		
		string to_string() const;
		//---------------------------------
		void optimize() { _expr = _expr->optimize(); }
		
		//Expression* expr() const { return _expr; };
		const Expression* expr() const { return _expr; };
	private:
		// const Expression* _expr;
		Expression* _expr;
}; 

} // namespace expr_tree
////////////////////////////////////////////////////////////////////////

namespace expr_tree {
	
class Node: public Expression {
	public:
		Node(Expression* link = 0) : Expression("Node"), _link(link) {}
		virtual ~Node() { delete _link; }
		virtual string to_string(int tab) const;
		//---------------------------------
		virtual Expression* optimize();
		
		virtual void set_link(Expression* link) { _link = link; }
		virtual Expression* get_link() const 	{ return _link; }
	private:
		Expression* _link; // will children get this?
};

class Num: public Expression {
	public:
		Num(int value) : Expression("Num"), _value(value) {}
		string to_string(int tab) const;
		//---------------------------------
		const int value() { return _value; }
		
		virtual void set_link(Expression* link) {
			std::cerr << "#! Unsupported operation expr_tree::Num.set_link()\n";
		}
		virtual Expression* get_link() const {
			std::cerr << "#! Unsupported operation expr_tree::Num.get_link()\n";
			return 0;
		}
	private:
		const int _value;
};

class B_Oper: public Expression{
	public:
		B_Oper(string name, Expression* left = 0, Expression* right = 0) : 
			Expression(name), _left(left), _right(right) {} // & vs *
		virtual ~B_Oper() {delete _left; delete _right;}
		string to_string(int tab) const;
		//---------------------------------
		
		virtual Expression* optimize();
		
		void set_left(Expression* left) { _left = left; }
		Expression* get_left() const 	{ return _left; }
		
		void set_right(Expression* right) { _right = right; }
		Expression* get_right() const 	  {  return _right; }
		
		virtual void set_link(Expression* link) { _right = link; }
		virtual Expression* get_link() const 	{ return _right; }
		
		//---------------------------------
		virtual int calculate(int left_value, int right_value) = 0;
	private:
		Expression* _left;
		Expression* _right;
}; // */

class Plus : public B_Oper {
	public: 
		Plus(Expression* left = 0, Expression* right = 0) : B_Oper("+", left,  right) {}
		
		virtual Expression* optimize();
		
		//---------------------------------
		virtual int calculate(int left_value, int right_value) {
			return left_value + right_value;
		}
};

} // namespace expr_tree
////////////////////////////////////////////////////////////////////////

typedef expr_tree::Expression Expression;
typedef expr_tree::Expr_tree Expr_tree;

#endif // _EXPR_TREE_HPP_
