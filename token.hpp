/** token.hpp
 * 
 * Classes of tokens
 * 
 * Tolken(name)
 *   Num(value)
 *   B_Oper(name)
 *     Plus
 *   Brack_L
 *   Brack_R
 * */ 
 
#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <string>
#include <algorithm>
#include <sstream>
#include <list>

#include <cctype>
#include <assert.h>

#include "expr_tree.hpp"
#include "BUILD.H"

using namespace std;
//----------------------------------------------------------------------

namespace token {
	
class Token;
	
class list_Token: public list<Token*> {
	public: ~list_Token();
};

class Token{
	public:
		Token(const string name) : _name(name) {}
		virtual ~Token() {}
		const string name() const {return _name;}
		virtual string to_string() const; // token.cpp
		//---------------------------------
		
		static const char* parse(const char* pointer, list_Token& lst); // token.cpp
		// how do you make me to override?
		
		virtual list_Token::const_iterator construct(
				list_Token::const_iterator iter,
				Expression* *current) const; // token.cpp
				
		virtual bool end() { return false; }
	private:
		const string _name;
};

class End : public Token {
	public:
		End() : Token("End") {}
		virtual bool end() { return true; }
};

} // namespace token
////////////////////////////////////////////////////////////////////////

namespace token {

class Num: public Token{
	public:
		Num(int value) : Token("Num"), _value(value) {}
		int value() const {return _value;}
		virtual string to_string() const;
		//---------------------------------
		static const char* parse(const char* pointer, list_Token& lst);
		
		virtual list_Token::const_iterator construct(
				list_Token::const_iterator iter,
				Expression* *current) const;
	private:
		const int _value;
};

class B_Oper: public Token{
	public:
		B_Oper(string name) : Token(name) {}
		virtual string to_string() const;
		//---------------------------------
};

class Plus : public B_Oper {
	public: 
		Plus() : B_Oper("+") {}
		//---------------------------------
		static const char* parse(const char* pointer, list_Token& lst);
		
		virtual list_Token::const_iterator construct(
				list_Token::const_iterator iter,
				Expression* *current) const;
};

class Brack_L: public Token{
	public:
		Brack_L() : Token("Brack_L") {}
		virtual string to_string() const;
		//---------------------------------
		static const char* parse(const char* pointer, list_Token& lst);
		
		virtual list_Token::const_iterator construct(
				list_Token::const_iterator iter,
				Expression* *current) const;
};

class Brack_R: public Token{
	public:
		Brack_R() : Token("Brack_R") {}
		virtual string to_string() const;
		//---------------------------------
		static const char* parse(const char* pointer, list_Token& lst);
		
		/*
		virtual list_Token::const_iterator construct(
				list_Token::const_iterator iter,
				Expression* *current) const; */
				
		virtual bool end() { return true; }
};

} // namespace token
////////////////////////////////////////////////////////////////////////

typedef token::Token Token;
typedef token::list_Token list_Token;

#endif // _TOKEN_HPP_
