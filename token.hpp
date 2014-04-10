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
#include <iostream>
#include <list>

#include <cctype>
#include <assert.h>

using namespace std;

inline int char_to_int(char ch) {
	assert( isdigit(ch) );
	return ch - '0';
}

namespace token {

class Token{
	public:
		Token(const string name) : _name(name) {}
		const string name() const {return _name;}
		//---------------------------------
		
		virtual string to_string() const// = 0;
		{
			ostringstream str;
			str << "Token(" << _name << ")";
			return str.str();
		} //*/
		
		//~ static  void parse(const char* str, list<Token>& lst) {
			//~ //return parse_(str, lst);
			//~ //return 
		//~ }
		//char* parse(const char* str, list<Token>& lst); // how make me to override?
	private:
		const string _name;
};

class list_Token: public list<Token*> {
	public:
		//*
		~list_Token() {
			std::cout << "list_Token is out\n";
			for(list_Token::iterator iter = this->begin();
					iter != this->end();
					iter++) {
				delete *iter;
			}
		} // */
		
		/*
		list_Token() {
			std::cout << "list_Token is in\n";
		} 
		
		~list_Token() {
			std::cout << "list_Token is out\n";
		} // */
		
		
};

} // namespace token
////////////////////////////////////////////////////////////////////////


namespace token {

class Num: public Token{
	public:
		Num(int value) : Token("Num"), _value(value) {}
		
		virtual string to_string() const{
			ostringstream str;
			str << "Num(" << _value << ")";
			return str.str();
		}
		
		static const char* parse(const char* pointer, list_Token& lst){ //////&
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
		
		virtual string to_string() const{
			ostringstream str;
			str << "B-Oper("  << "__" << name() << "__" << ")";
			return str.str();
		}
		
		//virtual int apply(int left, int right)
	private:
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
		
		virtual string to_string() const{
			ostringstream str;
			str << "Brack_L'('";
			return str.str();
		}
		
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
		
		virtual string to_string() const{
			ostringstream str;
			str << "Brack_R')'";
			return str.str();
		}
		
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

namespace token {
	
list_Token& parse_to_Token_list(string str);

}// namespace token
////////////////////////////////////////////////////////////////////////

#endif // _TOKEN_HPP_
