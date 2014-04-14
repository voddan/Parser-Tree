 /** test.cpp executable
 * 
 * This is the test file of 'Parser-Tree' project.
 * 
 * */ 

#include <stdio.h>
#include <iostream> 
#include <string>
#include <list>

#include "token.hpp"
#include "expr_tree.hpp"
#include "utils.hpp"

using namespace std;
using namespace utils;

//----------------------------------------------------------------------
void print_test_name(string name){
	cout << "#!---------------\n";
	cout << "#!--" << name << "--\n";
}

void test_Token_main();
void test_Token_parse();
void test_Expr_tree_parse();
void test_Expr_tree_optimize();

int main(){
	print_test_name("test.cpp");
	
	test_Token_main();
	
	test_Token_parse();
	
	test_Expr_tree_parse();
	
	test_Expr_tree_optimize();
	
	return 0;
}

void test_Token_main(){
	print_test_name("Token_main");
	// tests class Token
	
	using namespace token;
	list<Token*> lst;
	
	Num num1 (239);
	Num num2 (1);
	Token tok1 = num1;
	Token& pointer = num1;
	
	Plus opr1;
	
	cout << num1.to_string() << '\n';
	cout << tok1.to_string() << '\n';
	cout << opr1.to_string() << '\n';
	
	cout << "--------\n";
	
	cout << (pointer).to_string() << '\n';
	
	cout << "--------\n";
	
	cout << num1 << '\n';
	cout << tok1 << '\n';
	cout << opr1 << '\n';
	
	lst << &tok1;
	lst << &num2;
	lst << &opr1;
	lst << &num1;
	
	cout << lst;
}

void test_Token_parse(){
	print_test_name("Token_parse");
	// tests parsing string to tokens
	
	string strings[] = {
		"  123 +100 + (   400+)  ",
		"  123 +100 +  400  ",
		"  123 +100 + 0 + 400 + 0 ",
		"  123 +100 + 0 + 400 + 0 + 0 + 0 + ",
		"  123 +100 +  0 +  ",
		"  123 +100 +  400 + ",
		"    ",
		"__END__"
	};
	
	for(int i = 0; strings[i] != "__END__"; i++){
		cout << '"' << strings[i] << '"' << '\n';
		
		list_Token list_of_Tokens = token::parse_to_Token_list(strings[i]);
		cout << list_of_Tokens;
	}

}

void test_Expr_tree_parse(){
	print_test_name("Expr_tree_parse");
	// tests parsing tokens to expressions
	
	string strings[] = {
		"  123 +100 + (   400+)  ",
		"  123 +100 +  400  ",
		"  123 +100 + 0 + 400 + 0 ",
		"  123 +100 + 0 + 400 + 0 + 0 + 0 + ",
		"  123 +100 +  0 +  ",
		"  123 +100 +  400 + ",
		"    ",
		"__END__"
	};
	
	for(int i = 0; strings[i] != "__END__"; i++){
		cout << '"' << strings[i] << '"' << '\n';
		
		list_Token list_of_Tokens = token::parse_to_Token_list(strings[i]);
		//cout << list_of_Tokens;
		
		Expr_tree tree_of_Expr = expr_tree::parse_to_Expr_tree(list_of_Tokens);
		cout << tree_of_Expr.to_string() << '\n';
	}

}

void test_Expr_tree_optimize(){
	print_test_name("Expr_tree_optimize");
	// tests optimazing expressions
	
	string strings[] = {
		"  123 +100 + (   400+)  ",
		"  123 +100 +  400  ",
		"  123 +100 + 0 + 400 + 0 ",
		"  123 +100 + 0 + 400 + 0 + 0 + 0 + ",
		"  123 +100 +  0 +  ",
		"  123 +100 +  400 + ",
		"    ",
		"__END__"
	};
	
	for(int i = 0; strings[i] != "__END__"; i++){
		cout << '"' << strings[i] << '"' << '\n';
		
		list_Token list_of_Tokens = token::parse_to_Token_list(strings[i]);
		//cout << list_of_Tokens;
		
		Expr_tree tree_of_Expr = expr_tree::parse_to_Expr_tree(list_of_Tokens);
		
		tree_of_Expr.optimize();
		
		cout << tree_of_Expr.to_string() << '\n';
	}

}

