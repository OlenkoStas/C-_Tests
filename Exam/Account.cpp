#include "Account.h"

Account::Account()
{
}

Account::Account(string name, string surname, string email, string type)
{
	this->name = name;
	this->surname = surname;
	this->email = email;
	this->type = type;
	this->access = true;
}

Account::~Account()
{
}

string Account::GetName()
{
	return name;
}

string Account::GetSurname()
{
	return surname;
}

string Account::GetEmail()
{
	return email;
}

string Account::GetType()
{
	return type;
}

bool Account::GetAccess()
{

	return this->access;
}

void Account::SetAccess(bool access)
{
	this->access = access;
}

void Account::SetName(string name)
{
	this->name = name;
}

void Account::SetSurname(string surname)
{
	this->surname = surname;
}

void Account::SetEmail(string email)
{
	this->email = email;
}

void Account::SetType(string type)
{
	this->type = type;
}
//הכÿ גûגמהא ג פאיכ
ostream & operator<<(ostream & out, Account & obj)
{
	out << obj.name << " " << obj.surname << " " << obj.email << " " << obj.type << " " << obj.access << " ";
	return out;
}
//הכÿ גגמהא ג פאיכ
istream & operator>>(istream & in, Account & obj)
{
	in >> obj.name >> obj.surname >> obj.email >> obj.type >> obj.access;
	return in;
}
