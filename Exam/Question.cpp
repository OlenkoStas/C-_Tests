
#include "Question.h"

Question::Question(int x)
{
}

Question::Question()
{
	SetQuestion();
}

Question::~Question()
{
}
//показ вопроса 
int Question::ShowQuestion() const
{
	Yellow();
	cout << "\n  " << question << "\n\n";
	cout << "1) ";
	White();
	cout << this->ans_1 << "\n";
	Yellow();
	cout << "2) ";
	White();
	cout << this->ans_2 << "\n";
	Yellow();
	cout << "3) ";
	White();
	cout << this->ans_3 << "\n";
	Yellow();
	cout << "4) ";
	White();
	cout << this->ans_4 << "\n";
	
	return this->right_answer;
}
//создание вопроса
void Question::SetQuestion()
{
	cin.ignore();
	Yellow();
	cout << "\n¬ведите вопрос : ";
	White();
	getline(cin, this->question);
	Yellow();
	cout << "\n¬арианты ответов:\n";
	cout << "1)";
	White();
	getline(cin, ans_1);
	Yellow();
	cout << "2)";
	White();
	getline(cin, ans_2);
	Yellow();
	cout << "3)";
	White();
	getline(cin, ans_3);
	Yellow();
	cout << "4)";
	White();
	getline(cin, ans_4);
	Yellow();
	cout << "\n¬ведите номер правильного ответа :";
	White();
	cin >> right_answer;
}

string Question::GetQuestion()
{
	return question;
}

int Question::GetSizeQuestion()
{
	return this->question.size();
}
//дл€ вывода в файл
ostream & operator<<(ostream & out, Question & obj)
{
	out << obj.question << "\n";
	out << obj.ans_1 << "\n";
	out << obj.ans_2 << "\n";
	out << obj.ans_3 << "\n";
	out << obj.ans_4 << "\n";
	out << obj.right_answer << " ";
	return out;
}
//дл€ ввода в файл
istream & operator>>(istream & in, Question & obj)
{
	getline(in, obj.question);
	getline(in, obj.ans_1);
	getline(in, obj.ans_2);
	getline(in, obj.ans_3);
	getline(in, obj.ans_4);
	in >> obj.right_answer;
	return in;
}
