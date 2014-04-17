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

token::list_Token::~list_Token() {
	debug("list_Token is out\n"); 
	for(list_Token::iterator iter = this->begin();
			iter != this->end();
			iter++) {
		delete *iter;
	}
}

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

namespace token { // list_Token::const_iterator construct( list_Token::const_iterator iter, Expression* *current)
	
list_Token::const_iterator Token::construct(
		list_Token::const_iterator iter,
		Expression* *current) const {
	// may be an exeption
	cerr << "Unknow token '" << (*iter)->name() << "'\n";
	return ++iter;
}
	
list_Token::const_iterator Num::construct(
		list_Token::const_iterator iter,
		Expression* *current) const {
	const token::Num* tok = (token::Num*) *iter;
	(*current)->set_link( new expr_tree::Num( tok->value() ));
	return ++iter;		
}

list_Token::const_iterator Plus::construct(
		list_Token::const_iterator iter,
		Expression* *current) const {
	debug_detail("parsing Pluss[+] \n");
			
	expr_tree::Plus* plus = new expr_tree::Plus( (*current)->get_link(), 0 );
	(*current)->set_link( plus );
	
	// no way to implement this dump
	// debug_heavy(tree->to_string()); 
	
	(*current) = plus;
	
	return ++iter;
}

list_Token::const_iterator Brack_L::construct(
		list_Token::const_iterator iter,
		Expression* *current) const {
	debug_detail("parsing Brack_L \n");
	iter++;
	cerr << "Token Brack_L is unsupported yet\n";
	/*
	Node* node = new Node( 0 );
	(*current)->set_link( node );
	
	node -> set_link( parse_to_Expr_tree_recursive( &iter, end ).expr() );
	*/
	//iter--; // because of the for() loop
	return iter;
}

/*
list_Token::const_iterator Brack_R::construct(
		list_Token::const_iterator iter,
		Expression* *current) const {
	debug_detail("parsing Brack_R \n");
	iter++;
	cerr << "Token Brack_R is unsupported yet\n";
	// return from the whole parsing function
	//return *tree;
	return iter;
} */
	
} // namespace token
