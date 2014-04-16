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
