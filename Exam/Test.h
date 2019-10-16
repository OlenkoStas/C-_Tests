#pragma once
#include"Question.h"
#include"User.h"
#include<vector>
class Question;
class User;
void Yellow();
void White();
class Test
{
	string name_test;
	vector<Question> test;
	int amount_questions;
public:
	Test();
	Test(int amount_questions);
	~Test();
	string GetNameTest();
	void Show(User & user);
	void EditTest(string path_catalog);
	
	friend ostream & operator<<(ostream& out, Test& obj);
	
	friend istream & operator>>(istream& in, Test& obj);
};

