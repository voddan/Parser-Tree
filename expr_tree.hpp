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
		

class Num: public Expression{
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
		B_Oper(string name, Expression& left, Expression& right) : Expression(name), 
			_left(left), _right(right) {}
		
		string to_string() const{
			ostringstream str;
			str << "B-Oper(" << _left.to_string() << "__" << name() << "__" << _right.to_string() << ")";
			return str.str();
		}
		
		//virtual int apply(int left, int right)
	private:
		const Expression& _left;
		const Expression& _right;
};

class Plus : public B_Oper {
	public: 
		Plus(Expression& left, Expression& right) : B_Oper("+", left,  right) {}
		
		
};

} // namespace expr_tree
////////////////////////////////////////////////////////////////////////


typedef expr_tree::Expression Expression;

#endif // _EXPR_TREE_HPP_
