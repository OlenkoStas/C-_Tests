#include "Test.h"


Test::Test()
{
	
}
//����������� ������� ����
Test::Test(int amount_questions)
{
	this->amount_questions = amount_questions;
	for (int i = 0; i < this->amount_questions; ++i)
	{
		this->test.push_back((*new Question()));
	}
	cin.ignore();
	Yellow();
	cout << "������� �������� ����� :";
	White();
	getline(cin, name_test);
}

Test::~Test()
{
}
//���������� ��� �����
string Test::GetNameTest()
{
	return name_test;
}
//����� �����(��� ����������� � ��������������)
void Test::Show(User & user) 
{
	if (this->test.size())
	{
		int my_answer = 0;//����� ������������
		int right_answers = 0;//���-�� ���������� �������
		int num_question = 1;//����� �������
		for (auto &el : test)
		{
			int right_answ;
			cout << "\n������ ";
			cout << num_question << " :\n";
			right_answ = el.ShowQuestion();
			Yellow();
			cout << "\n\t����� : ";
			White();
			cin >> my_answer;
			if (my_answer == right_answ)
				++right_answers;
			++num_question;
			system("cls");
		}
		Yellow();
		cout << "\n\n\n\t\t���� �������.\n";
		White();
		Sleep(1000);
		//���������� ���������� � ���������
		int rez = ((double)right_answers / (double)this->amount_questions) * 100;
		cout << "\n\t���������� ���������� ������� : ";
		Yellow();
		cout << rez << " %\n";
		White();
		Sleep(1500);
		//��������� ������ � ���������� ������������
		if (user.GetType() == "user")
			user.AddStat(this->name_test, rez);
		system("cls");
	}
}
//�������������� �����
void Test::EditTest(string path_cat)
{
	FileHelper * fh = FileHelper::GetInstance();
	int choice = 0;
	bool is_continue = true;
	do {
		do {//�������
			system("cls");
			Yellow();
			cout << "\n\t\t�������������� ����� \""<<this->name_test<<"\"\n";
			White();
			cout << "\n1 - �������� ������\n"
				<< "\n2 - ������������� ������������\n"
				<< "\n3 - ���������  � ���������\n"
				<< "\n4 - ��������\n\n";
			cin >> choice;
		} while (choice < 1 && choice>4);
		if (choice == 1)
		{//���������� �������
			Question add(1);
			add.SetQuestion();//������� ������
			this->amount_questions++;
			this->test.push_back(add);//��������� � ����� �����
			cout << "\n������ ��������!\n";
			Sleep(1000);
		}
		else if (choice == 2)
		{//������������� ������������
			for (auto &el:this->test)
			{
				el.ShowQuestion();//����� �������
				do {//����� ��������
					Yellow();
					cout << "\n1";
					White();
					cout << "- �������������\n";
					Yellow();
					cout << "2";
					White();
					cout << "- ������� �� ��������� ������.\n";
					cin >> choice;
				} while (choice != 1 && choice != 2);
				if (choice == 2)continue;
				el.SetQuestion();//���� ������������� - ������������ ������������ ������
			}
			Yellow();
			cout << "\n\t�������������� ��������� �������!\n";
			White();
			Sleep(1000);
		}
		else if (choice == 3)
		{//��������� ���������
			fh->SaveTest(*this, path_cat);
			is_continue = false;
		}
		else
		{//������
			cout << "\n�������������� ��������!";
			is_continue = false;
			Sleep(1000);
		}
	} while (is_continue);
	system("cls");
}
//��� ������ � ����
ostream & operator<<(ostream & out, Test & obj)
{
	out << obj.name_test << "\n";
	out << obj.amount_questions << " ";
	
	for (auto &el : obj.test)
	     out << el ;
	return out;
}
//��� ����� �� �����
istream & operator>>(istream & in, Test & obj)
{

	getline(in, obj.name_test);
	in >> obj.amount_questions ;
	
	Question q(0);
	string str;
	
	while (!in.eof())
	{
		in >> q;
		obj.test.push_back(q);
	}
	obj.test.pop_back();
	return in;
}
