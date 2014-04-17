/** parsing_common.hpp
 * 
 * Common functions to parse:
 *   string -> list_Token
 *   list_Token -> Expr_tree
 * 
 * */ 
#include "parsing_common.hpp"

list_Token::const_iterator 
	expr_tree::parse_to_Expr_tree_recursive(
		list_Token::const_iterator iter,
		Expression* const root ) {
	// root - where to place
	
	debug_detail("parse_to_Expr_tree_recursive( " << (**iter).to_string() << " )\n");
	using namespace expr_tree;
	
	Expression* current = root;
	
	while( !(*iter)->end() ) {
		const Token* tok = *iter;
		iter = tok->construct(iter, &current);
	}
	
	// eats the END token
	return ++iter;
}

Expr_tree& expr_tree::parse_to_Expr_tree(list_Token& lst) {
	using namespace expr_tree;
	
	Expression* root = new Node(0);
	Expr_tree* tree = new Expr_tree( root );
	
	expr_tree::parse_to_Expr_tree_recursive(lst.begin(), root);
	
	return *tree;
}


const char* parse_space(const char* pointer, token::list_Token& lst){  // const ??? (char const * str)
	while(' ' == *pointer)
		pointer += 1;
	return pointer;
}

list_Token& token::parse_to_Token_list(string str){
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
	
	lst->push_back( new End() );
	
	return *lst;
}

