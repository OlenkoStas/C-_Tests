#pragma once
#include"Account.h"
#include"User.h"
#include"Test.h"

#include<vector>
#include<fstream>
#include<algorithm>
#include<direct.h>
#include<Windows.h>

using namespace std;

class User;
class Test;
void Yellow();
void White();
void Red();
struct Visitors
{
	string name, test;
	int num=0;
};
class FileHelper
{
	FileHelper();
public:
	~FileHelper();
	static FileHelper * GetInstance();

	void LoadAccounts(vector<Account> & v);
	void SaveAccounts(vector<Account> & v);
	void AddAccount(Account * acc);

	User LoadUser(string path);
	void SaveUser(User * user);

	int FindTest(string path, vector<string> * list_tests);

	bool AccessToTest(string login,string name_test);

	void LoadTestVisitors(vector<Visitors> & vec);
	void SaveTestVisitors(vector<Visitors> & vec);
	
	void LoadTest(Test& test,string path);
	void SaveTest(Test& test,string path);

	void SaveListTest(string full_path, vector<string>& v);

	bool LoadListCateg(vector<string> & List_categories);
	void SaveListCateg(vector<string> & List_categories);

	void CreateDirect(string path);
};

