#pragma once
#include<iostream>
#include<string>

using namespace std;

class Account
{
	string name,surname,email,type;
	bool access;
public:
	Account();
	Account(string name, string surname, string email, string type);
	~Account();

	string GetName();
	string GetSurname();
	string GetEmail();
	string GetType();
	bool GetAccess();

	void SetAccess(bool access);
	void SetName(string);
	void SetSurname(string);
	void SetEmail(string);
	void SetType(string);

	friend ostream & operator<<(ostream & out, Account & obj);
	friend istream & operator>>(istream & in, Account & obj);
};

