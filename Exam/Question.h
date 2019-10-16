#pragma once
#include"User.h"
#include"FileHelper.h"

void Yellow();
void White();

class Question
{
	string question;
	string ans_1;
	string ans_2;
	string ans_3;
	string ans_4;
	int right_answer;
public:
	Question(int);
	Question();
	~Question();
	int ShowQuestion()const;

	void SetQuestion();
	string GetQuestion();
	int GetSizeQuestion();
	friend ostream & operator<<(ostream& out, Question& obj);
	friend istream & operator>>(istream& in, Question& obj);
};

