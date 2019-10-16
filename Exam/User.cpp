#include "User.h"

User::User()
{
}

User::User(Account & account)
{
	this->acc = account;
}

User::User(string n, string s, string e, string t)
{
	this->acc.SetName(n);
	this->acc.SetSurname(s);
	this->acc.SetEmail(e);
	this->acc.SetType(t);
}

User::~User()
{
}

string User::GetName()
{
	return acc.GetName();
}
string User::GetSurname()
{
	return acc.GetSurname();
}
string User::GetEmail()
{
	return acc.GetEmail();
}
string User::GetType()
{
	return acc.GetType();
}

bool User::GetAccess()
{
	return this->acc.GetAccess();
}
void User::SetName()
{
	string tmp;
	cout << "\nВведите имя :";
	cin >> tmp;
	acc.SetName(tmp);
}
void User::SetSurname()
{
	string tmp;
	cout << "\nВведите фамилию :";
	cin >> tmp;
	acc.SetSurname(tmp);
}
void User::SetEmail()
{
	string tmp;
	cout << "\nЭлектронную почту :";
	cin >> tmp;
	acc.SetEmail(tmp);
}
void User::SetAccess(bool access)
{
	this->acc.SetAccess(access);
}
//показ имени и фамилии пользователя
void User::ShowData()
{
	Yellow();
	cout <<"\n\t\t"<<acc.GetName() << "\t" << acc.GetSurname();
	White();
}
//показ статистики
void User::ShowStatistic()
{
	ShowData();
	cout << "\n\t--------------------------"
		<< "\n\n\tРЕЗУЛЬТАТ\tТЕСТ\n";
	if (this->statistic.size() == 0)
		cout << "\nНе пройдено ни одного теста.\n";
	else
		
		for (auto &el : this->statistic)
		{
			Yellow();
			cout << "\n\t "<<el.rez<<" %\t\t";
			White();
			cout << el.name_test<<" ";
		}
}
//добавление статистики(после прохождения теста)
void User::AddStat(string test, int score)
{
	Stat add;
	add.name_test = test;
	add.rez = score;
	this->statistic.push_back(add);
}
//добавление пользователя преподавателя
void User::AddTeacher()
{
	FileHelper *p = FileHelper::GetInstance();
	string name, surname, email;
	Yellow();
	cout << "\n\t\tДобавление аккаунта 'TEACHER'.\n\n";
	White();
	cout << "Name    : ";
	cin >> name;
	cout << "\nSurname : ";
	cin >> surname;
	cout << "\nEmail  : ";
	cin >> email;
	Account acc(name, surname, email, "teacher");
	User teacher(acc);
	p->SaveUser(&teacher);
	p->AddAccount(&acc);
	cout << "\nАккаунт добавлен\n";
	Sleep(1000);
	system("cls");
}
//для вывода в файл
ostream & operator<<(ostream & out, User & obj)
{
	out << obj.acc.GetName() << " " << obj.acc.GetSurname() << " "
		<< obj.acc.GetEmail() << " " << obj.GetType() << "\n";
	
	if (obj.GetType() == "user")
		out << obj.statistic.size() << " ";
		for (auto &el : obj.statistic)
		{
			out << el.rez << "";
			out << el.name_test.c_str() << "\n";
		}
	return out;
}
//для ввода в файл
istream & operator>>(istream & in, User & obj)
{
	string str;
	int size;
	in >> str;
	obj.acc.SetName(str);
	in >> str;
	obj.acc.SetSurname(str);
	in >> str;
	obj.acc.SetEmail(str);
	in >> str;
	obj.acc.SetType(str);
	if (str == "user")
	{
		in >> size;
		User::Stat add;
		for (int i = 0; i < size; ++i)
		{
			in >> add.rez;
			getline(in, add.name_test,'\n');   
			obj.statistic.push_back(add);
		}
		
	}
	return in;
}
