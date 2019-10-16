#pragma once
#include<iostream>
#include<string>
//#include<Windows.h>
#include"Account.h"
#include"User.h"
#include"FileHelper.h"
#include<algorithm>

using namespace std;

void Yellow();
void White();

class Door
{
	Door();
public:
	static Door * PointDoor() 
	{
		static Door * p_door = new Door();
		return p_door;
	}
	~Door();

	User  EntryMenu();
	User  Avtorization();
	User  Registration();
	// если первый запуск программы - создаем учетку админа
	void FirstLoad(FileHelper * p,vector<Account> & v);
};

