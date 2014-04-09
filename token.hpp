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

using namespace std;

namespace Token_space{ // namespace Token_space
	
inline int char_to_int(char ch) {
	assert( isdigit(ch) );
	return ch - '0';
}

class Token{
	public:
		Token(const string name) : _name(name) {}
		const string name() const {return _name;}
		//---------------------------------
		
		virtual string to_string() const{
			ostringstream str;
			str << "Token(" << _name << ")";
			return str.str();
		}
		
		//~ static  void parse(const char* str, list<Token>& lst) {
			//~ //return parse_(str, lst);
			//~ //return 
		//~ }
		//char* parse(const char* str, list<Token>& lst); // how do i use 'const'?
	private:
		const string _name;
};

class Num: public Token{
	public:
		Num(int value) : Token("Num"), _value(value) {}
		
		virtual string to_string() const{
			ostringstream str;
			str << "Num(" << _value << ")";
			return str.str();
		}
		
		static const char* parse(const char* pointer, list<Token>& lst){
			char ch;
			
			if( !isdigit(ch = *pointer) ) return pointer;
			
			pointer += 1;
			int num = char_to_int(ch);
			
			while( isdigit(ch = *pointer) ) {
				pointer += 1;
				num *= 10;
				num += char_to_int(ch);
			}
			
			lst.push_back(Num(num));
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
	
		static const char* parse(const char* pointer, list<Token>& lst){
			if( '+' == *pointer ){
				lst.push_back(Plus());
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
		
		static const char* parse(const char* pointer, list<Token>& lst){
			if( '(' == *pointer ){
				lst.push_back(Brack_L());
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
		
		static const char* parse(const char* pointer, list<Token>& lst){
			if( ')' == *pointer ){
				lst.push_back(Brack_R());
				pointer += 1;
			}
			return pointer;
		}
};

} // namespace Token_space


namespace Token_space {
list<Token> parse_to_Token_list(string str);

const char* parse_space(const char* pointer, list<Token>& lst){  // const ???
	while(' ' == *pointer)
		pointer += 1;
	return pointer;
}

list<Token> parse_to_Token_list(string str){
	using namespace Token_space;
	typedef const char* (*Parse_function)(const char*, list<Token>&);
	
	list<Parse_function> parse_func_list;
	
	parse_func_list.push_back(Num::parse);
	parse_func_list.push_back(Plus::parse);
	parse_func_list.push_back(Brack_L::parse);
	parse_func_list.push_back(Brack_R::parse);
	
	parse_func_list.push_front(parse_space);
	//--------------------------------------------------------------
	list<Token> lst;
	
	const char* pointer  = &str[0];
	
	list<Parse_function>::const_iterator iter_func = parse_func_list.begin();
	while('\0' != *pointer){
		pointer = (*iter_func)(pointer, lst);
		iter_func++;
		if(parse_func_list.end() == iter_func)
			iter_func = parse_func_list.begin();
	}
	
	return lst;
}

}// namespace Token_space

#endif // _TOKEN_HPP_
