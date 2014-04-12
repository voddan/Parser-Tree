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

using namespace std;
//----------------------------------------------------------------------

namespace expr_tree { // namespace expr_tree

class Expression{
	public:
		Expression(const string name) : _name(name) {}
		virtual ~Expression() {}
		const string name() const {return _name;}
		
		//---------------------------------
		virtual string to_string() const{
			ostringstream str;
			str << "Expression(" << _name << ")";
			return str.str();
		}
		
	private:
		const string _name;
};

class Expr_tree  { // not an expression
	public:
		Expr_tree(Expression* expr) : _expr(expr) {}
		~Expr_tree() { 
			#ifdef DEBUG 
				std::cout << "Expr_tree is out\n"; 
			#endif
			delete _expr; 
		}
		
		string to_string() const{
			ostringstream str;
			str << "Expr_tree(" << ((_expr)? _expr->to_string() : " null ") << ")";
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
		~Node() { delete _link; }
		
		string to_string() const{
			ostringstream str;
			str << "Node(" << ((_link)? _link->to_string() : " null ") << ")";
			return str.str();
		}
		
		void set_Link(Expression* link) { _link = link; }
		Expression* get_Link() const 	{ return _link; }
	private:
		Expression* _link;
};



class Num: public Expression {
	public:
		Num(int value) : Expression("Num"), _value(value) {}
		
		string to_string() const{
			ostringstream str;
			str << "Num(" << _value << ")";
			return str.str();
		}
	private:
		const int _value;
};

class B_Oper: public Expression{
	public:
		B_Oper(string name, Expression* left = 0, Expression* right = 0) : 
			Expression(name), _left(left), _right(right) {} // & vs *
		virtual ~B_Oper() {delete _left; delete _right;}
		
		string to_string() const{
			ostringstream str;
			str << "B-Oper(" << ((_left)? _left->to_string() : " null ")
					 << "__" << name() << "__" 
					 << ((_right)? _right->to_string() : " null ") << ")";
			return str.str();
		}
		
		void set_Left(Expression* left) { _left = left; }
		Expression* get_Left() const 	{ return _left; }
		
		void set_Right(Expression* right) { _right = right; }
		Expression* get_Rightt() const 	  {  return _right; }
		
		//virtual int apply(int left, int right)
	private:
		Expression* _left;
		Expression* _right;
};

class Plus : public B_Oper {
	public: 
		Plus(Expression* left = 0, Expression* right = 0) : B_Oper("+", left,  right) {}
};

} // namespace expr_tree
////////////////////////////////////////////////////////////////////////


typedef expr_tree::Expression Expression;
typedef expr_tree::Expr_tree Expr_tree;

#endif // _EXPR_TREE_HPP_
