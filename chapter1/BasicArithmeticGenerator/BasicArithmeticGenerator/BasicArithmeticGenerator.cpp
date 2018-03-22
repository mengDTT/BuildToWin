// BasicArithmeticGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cctype>
#include "arithmetic_expression.h"

using namespace std;

static int exercise_num = 10;
static int number_range = 10;
static string exercise_file = "Exercises.txt";
static string answer_file = "Answers.txt";
static string grade_file = "Grade.txt";

bool is_even(const int argc)
{
	return argc % 2 == 0;
}

void miss_r_argument(void)
{
	cerr << "Argument missed! You have to specify the number range using  -r [d]" << endl;
}

void read_control_parameter(int argc, char * argv[])
{
	if (argc < 3) {
		miss_r_argument();
		return;
	}
	if (is_even(argc)) {
		cerr << "Argument number is not match!" << endl;
		return;
	}
	
	bool has_r{ false };
	int tmp_exercise_num{exercise_num};
	int tmp_number_range{number_range};
	string tmp_exercise_file{ exercise_file };
	string tmp_answer_file{ answer_file };
	for (int i = 1; i < argc; i +=2)
	{
		string arg = argv[i];

			
		if (arg == "-n" || arg== "-N")
			tmp_exercise_num= stoi(argv[i + 1]);
		else if (arg == "-r" || arg == "-R")
		{
			tmp_number_range= stoi(argv[i + 1]);
			has_r = true;
		}
		else if (arg == "-e" || arg == "-E")
		{
			tmp_exercise_file = argv[i + 1];
		}
		else if (arg == "-a" || arg == "-A")
		{
			tmp_answer_file = argv[i + 1];
		}

	}

	if (!has_r) 
	{
		miss_r_argument();
		return;
	}
	else
	{
		exercise_num = tmp_exercise_num;
		number_range = tmp_number_range;
		exercise_file = tmp_exercise_file;
		answer_file = tmp_answer_file;
	}	
}

int main(int argc, char * argv[])
{
	ios::sync_with_stdio(false);

	read_control_parameter(argc, argv);

	set<pair<wstring, MyFraction>> expressions;

	MyFraction f1 = MyFraction(1, 2) - MyFraction(9, 1);

	int count = 0;
	int operator_num = 3;
	while (count < exercise_num)
	{
		while (true)
		{
			arithmetic_expression exp(number_range, operator_num);
			exp.generate_expression();
			tree_node * p = exp.root;
			if (get<true>(expressions.insert({ p->exp,p->value })))
			{
				break;
			}
		}
		count++;
	}

	
	wofstream output1, output2;
	output1.open(exercise_file);
	output2.open(answer_file);


	vector<int> correct;
	vector<int> wrong;

	int exp_count = 1;
	locale a("C"), b("");
	for (const auto & item : expressions)
	{
		wstring exp = get<0>(item);
		MyFraction result_for_check = infix_expression_solve(exp);
		output1.imbue(a);
		output1 << exp_count << ". ";
		output1.imbue(b);
		output1<< format_output(exp) << endl;
		output2 << exp_count << ". " << result_for_check << endl;
		if (get<1>(item) == result_for_check)
		{
			correct.push_back(exp_count);
		}
		else
		{
			wrong.push_back(count);
		}
		exp_count++;
	}

	wofstream output3(grade_file);
	output3 << "Correct: " << correct.size() << " (";
	for (size_t i = 0; i < correct.size() ; ++i)
	{
		if( i == 0)
			output3 << correct[i];
		else
			output3 << ", " << correct[i] ;
	}
	output3 <<")" << endl;

	output3 << "Wrong: " << wrong.size() << " (";
	for (size_t i = 0; i < wrong.size(); ++i)
	{
		if (i == 0)
			output3 << wrong[i];
		else
			output3 << ", " << wrong[i];
	}
	output3 << ")" << endl;

	
    return 0;
}


