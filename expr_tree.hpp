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

#include "token.hpp"
#include "BUILD.H"

//using namespace std;
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
		
		
class Node: public Expression {
	public:
		Node(Expression* link = 0) : Expression("Node"), _link(link) {}
		virtual ~Node() { delete _link; }
		virtual string to_string(int tab) const;
		//---------------------------------
		
		virtual Expression* optimize() { 
			if(_link) _link = _link->optimize();
			// should I do like this?
			
			return this;  // debug
			/*
			Expression* t = _link;
			delete this;
			return t; // */
		}
		
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

//*
class B_Oper: public Expression{
	public:
		B_Oper(string name, Expression* left = 0, Expression* right = 0) : 
			Expression(name), _left(left), _right(right) {} // & vs *
		virtual ~B_Oper() {delete _left; delete _right;}
		string to_string(int tab) const;
		//---------------------------------
		
		virtual Expression* optimize() { 
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
		
		virtual Expression* optimize() { 
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
		
		//---------------------------------
		virtual int calculate(int left_value, int right_value) {
			return left_value + right_value;
		}
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
