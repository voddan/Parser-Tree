/** parsing_common.hpp
 * 
 * Common functions to parse:
 *   string -> list_Token
 *   list_Token -> Expr_tree
 * 
 * */ 
#include "parsing_common.hpp"

/*
Expr_tree& parse_to_Expr_tree_recursive(list_Token::const_iterator* iter_pointer, const list_Token::const_iterator end) {
	debug_detail("parse_to_Expr_tree_recursive( " << (***iter_pointer).to_string() << " )\n");
	
	using namespace expr_tree;
	list_Token::const_iterator& iter = *iter_pointer;
	
	Expr_tree* tree = new Expr_tree( new Node(0) );
	
	//Expression* current = tree->expr(); // a strange trouble with 'const'
	Expression* current = (Expression*) tree->expr();
	
	for(; iter != end; iter++){
		// want a switch here; problem with ' tipeid'
		const Token* tok = *iter;
		const string name = tok->name();
		
		if 	  ( name == "Num"){
			const token::Num* item = (token::Num*) tok;
			current->set_link( new Num( item->value() ));
			
		} else if ( name == "+"){
			debug_detail("parsing Pluss[+] \n");
			
			Plus* plus = new Plus( current->get_link(), 0 );
			current->set_link( plus );
			
			debug_heavy(tree->to_string()); 
			
			current = plus;
			
		} // use recursion !!!
		else if ( name == "Brack_L"){
			debug_detail("parsing Brack_L \n");
			iter++;
			
			Node* node = new Node( 0 );
			current->set_link( node );
			
			debug_heavy(tree->to_string());
			
			node -> set_link( (expr_tree::Expression*)
					  parse_to_Expr_tree_recursive( &iter, end ).expr() 
					);
			iter--; // because of the for() loop
			
		} else if ( name == "Brack_R"){
			debug_detail("parsing Brack_R \n");
			iter++;
			return *tree;
		} else {
			// may be an exeption
			cerr << "Unknow token '" << name << "'\n";
		}
	}
	
	return *tree;
}
// */

//*
list_Token::const_iterator 
	parse_to_Expr_tree_recursive(
		list_Token::const_iterator iter,
		Expression* const root ) {
	// root - where to place
	
	debug_detail("parse_to_Expr_tree_recursive( " << (***iter_pointer).to_string() << " )\n");
	using namespace expr_tree;
	
	Expression* current = root;
	
	while( !(*iter)->end() ) {
		const Token* tok = *iter;
		iter = tok->construct(iter, &current);
	}
	
	return iter;
} // */

//*
Expr_tree& expr_tree::parse_to_Expr_tree(list_Token& lst) {
	using namespace expr_tree;
	
	Expression* root = new Node(0);
	Expr_tree* tree = new Expr_tree( root );
	
	parse_to_Expr_tree_recursive(lst.begin(), root);
	
	return *tree;
} // */




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

