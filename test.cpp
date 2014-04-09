 /** test.cpp
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

typedef token::Token Token;
typedef expr_tree::Expression Expression;
//----------------------------------------------------------------------
void print_test_name(string name){
	cout << "#!---------------\n";
	cout << "#!--" << name << "--\n";
}

void test_Token_main();
void test_Token_parse();

int main(){
	print_test_name("test.cpp");
	
	test_Token_main();
	
	test_Token_parse();
	
	return 0;
}

void test_Token_main(){
	print_test_name("Token_main");
	
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
	
	using namespace token;
	
	/////
	char str1[] = "  123 +100 + (   400+)  ";
	
	list<Token*> list_of_Tokens = token::parse_to_Token_list(str1);
	cout << list_of_Tokens;

}

