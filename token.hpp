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

inline int char_to_int(char ch) {
	assert( isdigit(ch) );
	return ch - '0';
}

namespace token {
	
class Token;
	
class list_Token: public list<Token*> {
	public:
		~list_Token();
};

/*
list_Token::~list_Token() {
	debug("list_Token is out\n"); 
	for(list_Token::iterator iter = this->begin();
			iter != this->end();
			iter++) {
		// delete *iter;
		// a problem with warnings
	}
}
// */

class Token{
	public:
		Token(const string name) : _name(name) {}
		virtual ~Token() {}
		const string name() const {return _name;}
		virtual string to_string() const;
		//---------------------------------
		
		static const char* parse(const char* pointer, list_Token& lst); // how do you make me to override?
		
		/*
		virtual list_Token::const_iterator construct(
				list_Token::const_iterator iter,
				Expression* *current) {
			// may be an exeption
			cerr << "Unknow token '" << (*iter)->name() << "'\n";
			return iter;
		} // */
	private:
		const string _name;
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

		static const char* parse(const char* pointer, list_Token& lst){
			char ch;
			
			if( !isdigit(ch = *pointer) ) return pointer;
			
			pointer += 1;
			int num = char_to_int(ch);
			
			while( isdigit(ch = *pointer) ) {
				pointer += 1;
				num *= 10;
				num += char_to_int(ch);
			}
			
			lst.push_back(new Num(num));
			return pointer;
		}
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
	
		static const char* parse(const char* pointer, list_Token& lst){
			if( '+' == *pointer ){
				lst.push_back(new Plus());
				pointer += 1;
			}
			return pointer;
		}
};

class Brack_L: public Token{
	public:
		Brack_L() : Token("Brack_L") {}
		virtual string to_string() const;
		//---------------------------------
		
		static const char* parse(const char* pointer, list_Token& lst){
			if( '(' == *pointer ){
				lst.push_back(new Brack_L());
				pointer += 1;
			}
			return pointer;
		}
};

class Brack_R: public Token{
	public:
		Brack_R() : Token("Brack_R") {}
		virtual string to_string() const;
		//---------------------------------
		
		static const char* parse(const char* pointer, list_Token& lst){
			if( ')' == *pointer ){
				lst.push_back(new Brack_R());
				pointer += 1;
			}
			return pointer;
		}
};

} // namespace token
////////////////////////////////////////////////////////////////////////

typedef token::Token Token;
typedef token::list_Token list_Token;

#endif // _TOKEN_HPP_
