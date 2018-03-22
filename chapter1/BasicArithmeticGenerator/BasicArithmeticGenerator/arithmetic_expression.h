#pragma once
#include "fraction.h"
#include <string>
#include <vector>
#include <stack>
using namespace std;
struct tree_node
{
	tree_node(const MyFraction & f0 = { 0,1 }, wchar_t op0 = L'0', tree_node*left0 = nullptr, tree_node* right0 = nullptr) : value(f0), op(op0), left(left0), right(right0) 
	{
		exp = value.output_proper_fraction();
	};
	MyFraction value;
	wstring exp;
	wchar_t op;

	tree_node* left;
	tree_node* right;
};


class arithmetic_expression
{
public:
	arithmetic_expression(unsigned range = 10, unsigned operators = 2): number_range(range), operator_number(operators)
	{
		root = nullptr;
	};

	arithmetic_expression& generate_expression();
	void add_operator_node_to_tree(stack<tree_node*> &tree, wchar_t op);

	MyFraction generate_random_number();
	unsigned generate_operator();
	pair<MyFraction, bool> generate_random_number_or_operator();
	~arithmetic_expression();
	void tree_destroy(tree_node *root);
	tree_node * root;
	unsigned number_range;
	unsigned operator_number;
};

//wostream & operator<<(wostream &os, const arithmetic_expression & exp);
wstring infix_to_postfix_expression(const wstring & infix);
wstring postfix_to_infix_expression(const wstring & post);
MyFraction postfix_expression_solve(const wstring & postfix);
MyFraction infix_expression_solve(const wstring & infix);
MyFraction select_operation(const MyFraction & f1, const MyFraction & f2, wchar_t op);
wstring format_output(const wstring & expression);