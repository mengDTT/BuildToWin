#include "stdafx.h"
#include "arithmetic_expression.h"
#include <random>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cctype>


static wstring operators = L"-+x÷^";

void swap_subtree(tree_node * &mid, tree_node *&left, tree_node * &right)
{
	tree_node * tmp = left;
	mid->left = right;
	mid->right = tmp;
}
bool subtree_lesser(const tree_node * tree1, const tree_node * tree2)
{
	return (tree1->value < tree2->value) ? true : false;
}

void update_infix_expression(tree_node * current)
{
	tree_node * left = current->left;
	tree_node * right = current->right;

	wchar_t op = current->op;
	wchar_t left_op = left->op;
	wchar_t right_op = right->op;

	bool left_brace{ false };
	bool right_brace{ false };

	// 判断左表达式否需要加括号
	if ((op == L'x' || op == L'÷') && (left_op == L'+' || left_op == L'-'))
	{
		left_brace = true;
	}

	// 判断右表达式否需要加括号
	if (right->op != L'0')
	{
		switch (op)
		{
		case L'+':
			right_brace = (right->op == L'-');
			break;
		case L'-':
			right_brace = (right->op == L'+' || right->op == L'-');
			break;
		case L'x':
			right_brace = (right->op == L'+' || right->op == L'-' || right->op == L'÷');
			break;
		case L'÷':
			right_brace = (right->op == L'+' || right->op == L'-' || right->op == L'x' || right->op == L'÷');
			break;
		case L'^':
			right_brace = true;
			break;
		}
	}
	current->exp = (left_brace ? L"( " + left->exp + L" )" : left->exp) +
		L" " + wstring(&op, &op + 1) + L" " +
		(right_brace ? L"( " + right->exp + L" )" : right->exp);

}
wstring postfix_to_infix(tree_node * root)
{
	if (root != nullptr)
	{
		stack<tree_node*> stack_tree;
		tree_node* current = root;
		tree_node* previous = nullptr;


		while (current != nullptr || !stack_tree.empty())
		{
			while (current != nullptr)
			{
				stack_tree.push(current);
				current = current->left;
			}

			current = stack_tree.top();

			if (current->right == nullptr || current->right == previous)
			{
				if (current->op != L'0')
					update_infix_expression(current);
				stack_tree.pop();
				previous = current;
				current = nullptr;
			}
			else
			{
				current = current->right;
			}
		}
		return root->exp;
	}
	else
		return L"";

}

void arithmetic_expression::add_operator_node_to_tree(stack<tree_node*> &tree, wchar_t op)
{
	tree_node * right = tree.top(); tree.pop();
	tree_node * left = tree.top(); tree.pop();

	if (op == L'÷' && right->value.numerator == 0)
	{
		unsigned new_op_id;
		while (op == L'÷') //产生非÷新符号
		{
			new_op_id = generate_operator();
			op = operators[new_op_id];
		}
	}

	MyFraction f = select_operation(left->value, right->value, op);

	tree_node * mid = new tree_node(f, op, left, right);

	if ((op == L'+' || op == L'x') && subtree_lesser(right, left))
	{
		swap_subtree(mid, left, right);
	}

	if (op == L'-' && f.numerator < 0)
	{
		swap_subtree(mid, left, right);
		(mid->value).numerator = -f.numerator;
	}

	tree.push(mid);
}

arithmetic_expression& arithmetic_expression::generate_expression()
{
	stack<tree_node*> tree;

	unsigned item_count{ 0 };
	unsigned op_count{ 0 };

	while (op_count < operator_number)
	{
		if (item_count < 2 || item_count - 1 <= op_count )
		{
			MyFraction number = generate_random_number();
			tree_node* node = new tree_node(number);
			tree.push(node);
			item_count++;
		}
		else if (item_count <= operator_number)
		{
			pair<MyFraction, bool> next = generate_random_number_or_operator();
			if (next.second)
			{
				tree_node* node = new tree_node(next.first);
				tree.push(node);
				item_count++;
			}
			else
			{
				unsigned op_id = (next.first).numerator;
				wchar_t op = operators[op_id];

				add_operator_node_to_tree(tree, op);

				op_count++;
			}
		}
		else 
		{
			unsigned  op_id = generate_operator();
			wchar_t op = operators[op_id];

			add_operator_node_to_tree(tree, op);

			op_count++;
		}
	}
	root = tree.top();
	postfix_to_infix(root);
	return *this;
}

MyFraction arithmetic_expression::generate_random_number()
{
	static default_random_engine e((unsigned)time(nullptr));
	static uniform_int_distribution<unsigned> natural_fraction(0, 1);
	static uniform_int_distribution<unsigned> natural(1, number_range - 1);
	
	MyFraction result;
	unsigned choice = natural_fraction(e);
	if (choice == 0)
	{
		result = MyFraction(natural(e), 1).reduction();
	}
	else if (choice == 1)
	{
		unsigned a = natural(e);
		unsigned b = natural(e);
		result = MyFraction(a, b).reduction();
	}

	return result;
}

unsigned arithmetic_expression::generate_operator()
{
	static default_random_engine e((unsigned)time(nullptr));
	static uniform_int_distribution<unsigned> random_operator(0, 3);

	return random_operator(e);
}


wstring infix_to_postfix_expression( const wstring&  infix)
{
	wistringstream input(infix);
	stack<int> Stack;
	wstring postfix_expression;

	for (wstring token; getline(input, token, L' ');)
	{
		wchar_t c = token.at(0);
		auto pos1 = operators.find(c);

		if (pos1 != wstring::npos)
		{
			if (Stack.empty())
				Stack.push(pos1);
			else
			{
				while (!Stack.empty())
				{
					int priority1 = pos1 / 2;
					int priority2 = Stack.top() / 2;
					if (priority2 > priority1 || (priority2 == priority1 && c != L'^'))
					{
						int pos2 = Stack.top();
						Stack.pop();
						postfix_expression.append(wstring(1, operators[pos2]).append(L" "));
					}
					else
						break;
				}
				Stack.push(pos1);
			}
		}
		else if (c == L'(')
		{
			Stack.push(-2); //  -2 stands for 'C'
		}
		else if (c == L')')
		{
			while (!Stack.empty() && Stack.top() != -2)
			{
				int pos2 = Stack.top();
				Stack.pop();
				postfix_expression.append(wstring(1, operators[pos2]).append(L" "));
			}
			Stack.pop();
		}
		else
		{
			postfix_expression.append(token).append(L" ");
		}
	}

	while (!Stack.empty())
	{
		int pos2 = Stack.top();
		Stack.pop();
		postfix_expression.append(wstring(1, operators[pos2]).append(L" "));
	}

	return postfix_expression;
}

pair<MyFraction, bool> arithmetic_expression::generate_random_number_or_operator()
{
	static default_random_engine e((unsigned)time(nullptr));
	static uniform_int_distribution<unsigned> number_or_operator(0, 1);

	unsigned r = number_or_operator(e);
	if (r == 1) 
	{
		unsigned op = generate_operator();
		return { MyFraction(op, 1), false };
	}
	else
	{
		MyFraction number = generate_random_number();
		return{ number, true };
	}
}


MyFraction infix_expression_solve(const wstring & infix)
{
	wstring postfix = infix_to_postfix_expression(infix);
	return postfix_expression_solve(postfix);
}

struct expression_with_op
{
	wstring expression;
	wchar_t op;
};

wstring postfix_to_infix_expression(const wstring & post)
{
	wistringstream input(post);
	stack<expression_with_op> expressions;

	for (wstring token; getline(input, token, L' ');)
	{
		wchar_t c = token.at(0);
		if (L'0' <= c && c <= L'9')
		{
			struct expression_with_op item ={ token, c };
			expressions.push(item);
		}
		else
		{
			auto right = expressions.top(); expressions.pop();
			auto left = expressions.top(); expressions.pop();

			bool left_brace = false;
			bool right_brace = false;

			// 判断左表达式否需要加括号
			if ((c == L'x' || c == L'÷') && (left.op == L'+' || left.op == L'-'))
			{
				left_brace = true;
			}
			if ((left.op < L'0' || L'9' < left.op) && c == L'^')
			{
				left_brace = true;
			}

			// 判断右表达式否需要加括号
			if (right.op < L'0' || L'9' < right.op)
			{
				switch (c)
				{
				case L'+':
					right_brace = (right.op == L'-');
					break;
				case L'-':
					right_brace = (right.op == L'+' || right.op == L'-');
					break;
				case L'x':
					right_brace = (right.op == L'+' || right.op == L'-' || right.op == L'÷');
					break;
				case L'÷':
					right_brace = (right.op == L'+' || right.op == L'-' || right.op ==L'x' || right.op == L'÷');
					break;
				case L'^':
					right_brace = true;
					break;
				}
			}

			wstring new_expression =
				(left_brace ? L"(" + left.expression + L")" : left.expression) +
				L" " + wstring(&c, &c + 1) + L" " +
				(right_brace ? L"(" + right.expression + L")" : right.expression);
				expressions.push({ new_expression, c });
		}
	}
	return expressions.top().expression;
}

MyFraction postfix_expression_solve(const wstring & postfix)
{
	wistringstream input(postfix);
	stack<MyFraction> Stack;

	for (wstring token; getline(input, token, L' ');)
	{
		wchar_t c = token.at(0);
		auto pos1 = operators.find(c);
		if (pos1 == wstring::npos)
		{
			size_t slash_index = token.find(L'/');
			int a = stoi(token.substr(0, slash_index));
			int b = stoi(token.substr(slash_index + 1));
			Stack.push(MyFraction(a, b));
		}
		else
		{
			MyFraction f2 = Stack.top(); Stack.pop();
			MyFraction f1 = Stack.top(); Stack.pop();
			MyFraction f3 = select_operation(f1, f2, c);
			Stack.push(f3);
		}
	}

	MyFraction result = Stack.top();
	return result.reduction();
}

MyFraction select_operation(const MyFraction & f1, const MyFraction & f2, wchar_t op)
{
	MyFraction result;
	switch (op) 
	{
	case L'+': result = f1 + f2; break;
	case L'-': result = f1 - f2; break;
	case L'x': result = f1 * f2; break;
	case L'÷': result = f1 / f2; break;
	}

	return result;
}

wstring format_output(const wstring & expression)
{
	wistringstream input(expression);

	wstring result;
	for (wstring token; getline(input, token, L' ');)
	{
		wchar_t c = token.at(0);
		
		if (L'0' <= c && c <= L'9')
		{
			size_t slash_index = token.find(L'/');
			int a = stoi(token.substr(0, slash_index));
			int b = stoi(token.substr(slash_index + 1));
			result.append(MyFraction(a, b).format_output());
			result.append(L" ");
		}
		else
		{
			result.append(token);
			result.append(L" ");
		}	
	}
	return result;
}

arithmetic_expression::~arithmetic_expression()
{
	tree_destroy(root);
}

void arithmetic_expression::tree_destroy(tree_node *root)
{
	tree_node * current = root;
	if (current != nullptr)
	{
		tree_destroy(current->left);
		tree_destroy(current->right);
		delete current;
	}
	current = nullptr;
	
}
