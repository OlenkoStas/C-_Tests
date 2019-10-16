#pragma once
#include"Account.h"
#include"FileHelper.h"

#include<vector>
#include<iostream>
#include<string>
#include<Windows.h>

using namespace std;

void Yellow();
void White();

class User
{
	Account acc;
	struct Stat
	{
		string name_test="";
		int rez=0;
	};
	vector<Stat> statistic;
public:
	User();
	User(Account & account);
	User(string, string, string, string);
	~User();
	
	string GetName();
	string GetSurname();
	string GetEmail();
	string GetType();
	bool GetAccess();

	void SetName();
	void SetSurname();
	void SetEmail();
	void SetAccess(bool access);

	void ShowData();
	void ShowStatistic();
	void AddStat(string, int);

	void AddTeacher();

	friend ostream & operator<<(ostream & out, User & obj);
	friend istream & operator>>(istream & in, User & obj);
	
};

