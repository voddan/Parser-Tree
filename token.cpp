/** token.cpp
 * 
 * Implementation of Tokens
 * 
 * list_Token& parse_to_Token_list(string str);
 * */ 
 
#include <string>
#include <algorithm>
#include <sstream>
#include <list>

#include <cctype>
#include <assert.h> 

#include "token.hpp"
#include "BUILD.H"

#include "parsing_common.hpp"

using namespace std;
using namespace token;

// why do I do this here, but not in token.hpp
//*
token::list_Token::~list_Token() {
	debug("list_Token is out\n"); 
	for(list_Token::iterator iter = this->begin();
			iter != this->end();
			iter++) {
		delete *iter;
		// a problem with warnings
	}
}
// */

namespace token { // string to_string() const
	
string Token::to_string() const {
			ostringstream str;
			str << "Token(" << _name << ")";
			return str.str();
		}
		
string Num::to_string() const {
		ostringstream str;
		str << "Num(" << _value << ")";
		return str.str();
	}
	
string B_Oper::to_string() const {
		ostringstream str;
		str << "B-Oper("  << "__" << name() << "__" << ")";
		return str.str();
	}
	
string Brack_L::to_string() const {
		ostringstream str;
		str << "Brack_L'('";
		return str.str();
	}
	
string Brack_R::to_string() const {
			ostringstream str;
			str << "Brack_R')'";
			return str.str();
		}
	
} // namespace token


inline int char_to_int(char ch) {
	assert( isdigit(ch) );
	return ch - '0';
}

namespace token { // static const char* parse(const char* pointer, list_Token& lst)

const char* Num::parse(const char* pointer, list_Token& lst){
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

const char* Plus::parse(const char* pointer, list_Token& lst){
	if( '+' == *pointer ){
		lst.push_back(new Plus());
		pointer += 1;
	}
	return pointer;
}

const char* Brack_L::parse(const char* pointer, list_Token& lst){
	if( '(' == *pointer ){
		lst.push_back(new Brack_L());
		pointer += 1;
	}
	return pointer;
}

const char* Brack_R::parse(const char* pointer, list_Token& lst){
			if( ')' == *pointer ){
				lst.push_back(new Brack_R());
				pointer += 1;
			}
			return pointer;
		}

} // namespace token
/*
const char* parse_space(const char* pointer, token::list_Token& lst){  // const ??? (char const * str)
	while(' ' == *pointer)
		pointer += 1;
	return pointer;
}

namespace token {
	
list_Token& parse_to_Token_list(string str){
	using namespace token;
	typedef const char* (*Parse_function)(const char*, list_Token&);
	
	list<Parse_function> parse_func_list;
	
	parse_func_list.push_back(Num::parse);
	parse_func_list.push_back(Plus::parse);
	parse_func_list.push_back(Brack_L::parse);
	parse_func_list.push_back(Brack_R::parse);
	
	parse_func_list.push_front(parse_space);
	//--------------------------------------------------------------
	list_Token* lst = new list_Token();
	
	const char* pointer  = &str[0];
	
	list<Parse_function>::const_iterator iter_func = parse_func_list.begin();
	while('\0' != *pointer){
		pointer = (*iter_func)(pointer, *lst);
		iter_func++;
		if(parse_func_list.end() == iter_func)
			iter_func = parse_func_list.begin();
	}
	
	return *lst;
}

}// namespace token
*/
