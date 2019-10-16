#pragma once
#include"Test.h"
#include"Account.h"
#include"User.h"
#include"FileHelper.h"

#include<direct.h>
#include<fstream>
#include<iomanip>


void Yellow();
void White();
void Red();

enum color { BLACK = 0, RED = 12, YELLOW = 14, WHITE };

class Application
{
	Application();
public:
	
	~Application();
	static Application * GetInstance();

	void UserMenu(User * user);
	void TeacherMenu(User * user);
	void AdminMenu(User * user);

	void UnLockUser();
	void EditTest(string path_category);
	void OpenTest(string path_category, User & user);

	void AddTest(string path_category);
	void DeleteTest(string path_category);

	void SelectCategory(string & path_category);
	void EditData(User & user);
	void ShowAccounts(vector<Account> & vec);
	void ChangeAccess();

	void AddCategory();
	void DelCategory();
};

