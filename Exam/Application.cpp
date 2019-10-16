#include "Application.h"

Application::Application()
{
}

Application::~Application()
{
}

Application * Application::GetInstance()
{
	static Application * p = new Application;
	return p;
}

void Application::UserMenu(User * user)
{
	FileHelper * fh = FileHelper::GetInstance();
	string path;
	int choice;
	system("cls");
	if (user->GetAccess())//�������� ������� ����� � ���������
		do {
			do {
				system("cls");
				Yellow();cout << "\n\n\t\t\t����\n\n\n\t1 - "; White();
				cout << "������� ����";
				Yellow(); cout << "\n\n\t2 - "; White(); cout << "����������";
				Yellow(); cout << "\n\n\t0 - "; White(); cout << "�����\n";
				cin >> choice;
				if (choice == 0)
				{
					fh->SaveUser(user);
					exit(0);
				}
			} while (choice != 1 && choice != 2);

			if (choice == 1)
			{
				string path_category = "\\Tests\\";
				SelectCategory(path_category);//����� ��������� ������
				OpenTest(path_category, *user);//�������� �����
				system("cls");
			}
			else
			{//����� ����������
				system("cls");
				user->ShowStatistic();
			}

			do {
				Yellow();
				cout << "\n\n\n\t\t���������� ������?\n";
				White();
				cout << "\t1 - ��\n"
					<< "\t2 - ���\n";
				cin >> choice;
			} while (choice != 1 && choice != 2);
			if (choice == 2)
			{//����� �� ���������
				fh->SaveUser(user);
				exit(0);
			}
			system("cls");
		} while (true);
	else
	{
		Red();
		cout << "\n\n\n\t��� ������� ������������.���������� � ��������������!\n\n";
		White();
	}
	Sleep(3000);
	exit(0);
}

void Application::TeacherMenu(User * user)
{
	string path_category;
	int choice = 0;
	system("cls");
	if (user->GetAccess())//�������� ������� ����� � ���������
	{
		do {
			do {
				Yellow(); cout << "\n\n\t\t\t����(�������������)\n\n\n\t1 - "; White(); cout << "�������� ����";
				Yellow(); cout << "\n\n\t2 - "; White(); cout << "������� ����";
				Yellow(); cout << "\n\n\t3 - "; White(); cout << "������������� ����";
				Yellow(); cout << "\n\n\t4 - "; White(); cout << "�������������� ������ � �����";
				Yellow(); cout << "\n\n\t5 - "; White(); cout << "�������� ���������";
				Yellow(); cout << "\n\n\t6 - "; White(); cout << "������� ���������";
				Yellow(); cout << "\n\n\t0 - "; White(); cout << "�����\n";
				cin >> choice;
				if (choice == 0)exit(0);
			} while (choice < 1 && choice > 6);
			if (choice >= 1 && choice <= 3)
			{
				string path_category="\\Tests\\";
				if (choice >= 1 && choice <= 3)
					SelectCategory(path_category);//����� ��������� ������
				if (path_category != "\\Tests\\")
				{
					switch (choice)
					{
					case 1:AddTest(path_category); break;
					case 2:DeleteTest(path_category); break;
					case 3:EditTest(path_category); break;
					}
				}
			}
			else if(choice==4)UnLockUser();
			else if (choice == 5)AddCategory();
			else DelCategory();
			system("cls");
		} while (true);
	}
	else
	{
		Red();
		cout << "\n\n\n\t��� ������� ������������.���������� � ��������������!\n\n";
		White();
	}
	Sleep(3000);
	exit(0);
}

void Application::AdminMenu(User * user)
{
	FileHelper * fh = FileHelper::GetInstance();
	int choice = 0;
	do {
		do {
			Yellow(); cout << "\n\n\t\t\t����(�������������)\n\n\n\t1 - "; White(); cout << "�������� ������������(�������������)";
			Yellow(); cout << "\n\n\t2 - "; White(); cout << "�������� ����";
			Yellow(); cout << "\n\n\t3 - "; White(); cout << "������� ����";
			Yellow(); cout << "\n\n\t4 - "; White(); cout << "������������� ����";
			Yellow(); cout << "\n\n\t5 - "; White(); cout << "�������� ������ ������������";
			Yellow(); cout << "\n\n\t6 - "; White(); cout << "�������� ������ ����� � �������";
			Yellow(); cout << "\n\n\t0 - "; White(); cout << "�����\n";
			cin >> choice;
			if (choice == 0)
			{
				fh->SaveUser(user);
				exit(0);
			}
		} while (choice < 1 && choice > 6);
		if(choice==1)user->AddTeacher();
		else if (choice >= 2 && choice <= 4)
		{
			string path_category = "\\Tests\\";
			SelectCategory(path_category);//����� ��������� ������
			if (path_category != "\\Tests\\")
			{
				switch (choice)//������ � ������
				{
				case 2:AddTest(path_category); break;
				case 3:DeleteTest(path_category); break;
				case 4:EditTest(path_category); break;
				}
			}
		}
		else if(choice==5)ChangeAccess();
		else EditData(*user);

		system("cls");
	} while (true);
}
// + ���� �������������� �������
void Application::UnLockUser()
{
	FileHelper * fh = FileHelper::GetInstance();
	vector<Visitors> vec;
	string name, surname, test_name,test;
	fh->LoadTestVisitors(vec);//�������� ������ ��������� ����������� �����
	system("cls");
	Yellow();
	cout << "\n\n\n\n\t\t������ ��� �������������";
	White();
	cout << "\n\n\t���     : ";
	cin >> name;
	cout << "\n\t������� : ";
	cin >> surname;
	cout << "\n\t�������� ����� :";
	cin.ignore();
	getline(cin, test_name);
	test = test_name;
	
	vector<Visitors>::iterator it;
	it = find_if(vec.begin(), vec.end(), [name,surname,test](Visitors stud)//����� �������� �� ��������� ������
	{
		return stud.name == (name + surname) && stud.test == test;
	});
	if (it != vec.end())//���� ������
	{
		int choice;
		do {
			Yellow();
			cout << "\n�������������� ������ �������� " << name << " " << surname << " � ����� \"" << test_name << "\"?\n";
			White();
			cout << "\n1 - ��\n"
				 << "2 - ���\n\n";
			cin >> choice;
		} while (choice != 1 && choice != 2);
		if (choice == 1)
		{
			(*it).num--;//���� �������������� �������
			Yellow();
			cout << "\n������ �������������!\n";
			White();
			Sleep(1000);
			system("cls");
		}
		fh->SaveTestVisitors(vec);
	}
	else
	{
		Red();
		cout << "\n\t�� ������\n";
		Sleep(1000);
		White();
	}
	system("cls");
}
//�������������� �����
void Application::EditTest(string path_category)
{
	FileHelper * fh = FileHelper::GetInstance();
	Test test;
	fh->LoadTest(test, path_category);//�������� �����
	if (test.GetNameTest() != "")
		test.EditTest(path_category);//�������������� �����
}
//����� �����
void Application::OpenTest(string path_category, User & user)
{
	FileHelper * fh = FileHelper::GetInstance();
	Test test;
	fh->LoadTest(test, path_category);//�������� �����
	if (test.GetNameTest() != "")//�������� ��� ���� ����������
		if (fh->AccessToTest((user.GetName() + user.GetSurname()), test.GetNameTest()))//�������� ������� �������� � �����
			test.Show(user);
		else
		{
			Red();
			cout << "\n\n\n\t���� ������������.���������� � �������������.\n";
			White();
			Sleep(1500);
		}
}
//���������� �����
void Application::AddTest(string path_category)
{
	FileHelper * fh = FileHelper::GetInstance();
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);
	string path_dir = buf + path_category;
	_mkdir(path_dir.c_str());//������� ����� ���� ����

	//������� ����
	system("cls");
	int amount_questions;
	Yellow();
	cout << "������� ���������� �������� :";
	White();
	cin >> amount_questions;
	Test new_test(amount_questions);
	//��������� ����
	fh->SaveTest(new_test, path_category);
	//��������� � ������ ������ �����������
	ofstream out(path_dir + "List.txt", ios::app);
	if (out.is_open())
		out << new_test.GetNameTest() << "\n";
	else
		cerr << "�� �������� ������ ������\n";
	out.close();
	system("cls");
}
//�������� �����
void Application::DeleteTest(string path_category)
{
	FileHelper * fh = FileHelper::GetInstance();
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);

	vector<string>  list_tests;
	//������� ������ ����
	int num_test = fh->FindTest(path_category, &list_tests);
	
	if (num_test)//���� ������ ���� ������
	{
		string path_test = buf + path_category + list_tests[num_test - 1] + ".txt";
		if (remove(path_test.c_str()) != 0)//�������� �����
			cerr << "\n������ �������� �����.\n";
		else
		{
			Yellow();
			cout << "���� ������ �������\n";
			White();
			vector<string>::iterator it = list_tests.begin();
			//������� ������ �� ������ ������
			list_tests.erase(it + (num_test - 1));
			//��������� ����������� ������
			fh->SaveListTest(buf + path_category + "List.txt", list_tests);
		}
		Sleep(1500);
		system("cls");
	}
}
//����� ��������� ������
void Application::SelectCategory(string & path_category)
{
	FileHelper *fh = FileHelper::GetInstance();
	vector<string> list_cat;
	system("cls");
	//�������� ������ ������������ ���������
	fh->LoadListCateg(list_cat);
	if (list_cat.size() != 0)//���� ������ �� ������
	{
		Yellow();
		cout << "\n\t�������� ��������� :\n\n";
		White();
		int i = 1;
		int choice;
		for (auto &el : list_cat)
		{
			Yellow();
			cout << i << ") ";
			White();
			cout << el << "\n";
			++i;
		}
		Yellow();
		cout << "0) ";
		White();
		cout << "�������� � ������� ����\n";
		do {
			Yellow();
			cout << "\n\t����� : ";
			White();
			cin >> choice;
		} while (choice<0 || choice>list_cat.size());
		if (choice == 0)return;
		path_category += list_cat[choice - 1] + "\\";
	}
	else
	{//���� ������ ������
		cout << "\n������ ��������� ������!\n";
		//��������� ���������
		AddCategory();
		//��������� ����������� ������ ���������
		vector<string> List_categories;
		fh->LoadListCateg(List_categories);
		//�������� ���� � ��������� ��� ��������
		path_category += List_categories[0] + "\\";
	}
}
//������� �������������� ������ ������(������ ��� ��������������)
void Application::EditData(User & user)
{
	user.SetName();
	user.SetSurname();
	user.SetEmail();
}
//����� ���� ��������� ��� ��������� ������� � ������� (������ ��� ��������������)
void Application::ShowAccounts(vector<Account> & vec)
{
	system("cls");
	//��������� �� ������� 
	sort(vec.begin(), vec.end(), [](Account a, Account b) {
		return a.GetSurname() < b.GetSurname();
	});
	if (vec.size())
	{
		Yellow();
		cout << "\n\n\t������ ���������\n";
		White();
		int i = 1;
		for (auto &el : vec)
		{
			cout << "\n"<<i<<") " <<setw(15) << left <<el.GetSurname() << setw(15) << left << el.GetName() <<"'"<< setw(15) << left << el.GetType()+"'";
			if (el.GetAccess())
			{
				Yellow();
				cout << "��������";
				White();
			}
			else
			{
				Red();
				cout << "������������";
				White();
			}
			++i;
		}
	}
	else
		cout << "\n�� ���������������� �� ������ ������������!\n";
	cout << "\n";
}
//��������� ������� � ������� (������ ��� ��������������)
void Application::ChangeAccess()
{
	FileHelper *fh = FileHelper::GetInstance();
	vector<Account> vec;
	int num_acc = 0;
	//�������� ���� ���������
	fh->LoadAccounts(vec);
	//����� ���� ���������
	ShowAccounts(vec);
	//����� ��������
	do {
		Yellow();
		cout << "\n������� ����� �������� ����� �������� ������ : ";
		White();
		cin >> num_acc;
	} while (num_acc < 1 || num_acc > vec.size());
	if (vec[num_acc - 1].GetAccess())//��������� �������
		vec[num_acc - 1].SetAccess(false);
	else vec[num_acc - 1].SetAccess(true);
	Yellow();
	cout << "\n������ �������!\n";
	White();
	fh->SaveAccounts(vec);//���������� ������������ ������
	Sleep(1000);
	system("cls");
}
//���������� ��������� ������
void Application::AddCategory()
{
	FileHelper * fh = FileHelper::GetInstance();
	vector<string> List_categories;
	string name_category;
	bool is_load;//��� �������� ���������� ������ ��� ���
	//�������� ������ ���������
	is_load = fh->LoadListCateg(List_categories);
	if (is_load)
	{//���������� ���������
		Yellow();
		cout << "\n������� �������� ����� ��������� : ";
		White();
		cin.ignore();
		getline(cin, name_category);
		vector<string>::iterator it;
		//���� ���������� �� ����� �� ���������
		it = find_if(List_categories.begin(), List_categories.end(), [name_category] (string str) {return name_category == str;});

		if (it == List_categories.end())//���� ���
		{
			List_categories.push_back(name_category);//��������� � ������ ����� ���������
			fh->CreateDirect(name_category);//������� �������
			fh->SaveListCateg(List_categories);//��������� ����� ������ ���������
			Yellow();
			cout << "\n��������� ��������� �������!";
			White();
			Sleep(1000);
			system("cls");
		}
		else
		{
			Red();
			cout << "\n��������� � ����� ��������� ��� ����������!\n";
			White();
		}
	}
	else
	{
		cerr << "\n������ �������� ������ ���������\n";
	}
}
//�������� ���������
void Application::DelCategory()
{
	FileHelper * fh = FileHelper::GetInstance();
	string path_category = "\\Tests\\";
	int choice;
	do {//�������������� ������������
		system("cls");
		Red();
		cout << "\n\n\t\t��������\n\n"
			<< "\t��� ���������� �������� ����� ������� !\n\n";
		White();
		cout << "1 - ����������\n"
			<< "2 - ��������\n";
		cin >> choice;
	} while (choice != 1 && choice != 2);
	White();
	if (choice == 1)//���������� ��������
	{
		vector<string>list_tests;
		vector<string>list_category;
		//�������� ������ ���������
		fh->LoadListCateg(list_category);
		//����� ��������� ���������
		if (list_category.size() != 0)
		{
			Yellow();
			cout << "\n\t�������� ��������� :\n\n";
			White();
			int i = 1;
			for (auto &el : list_category)
			{
				Yellow();
				cout << i << ") ";
				White();
				cout << el << "\n";
				++i;
			}
			do {
				Yellow();
				cout << "\n\t����� : ";
				White();
				cin >> choice;
			} while (choice<1 || choice>list_category.size());
			vector<string>::iterator it = list_category.begin();
			path_category += list_category[choice - 1] + "\\";//���� � ���������� ��������
			list_category.erase(it + (choice - 1));//������� �� ������ ��������
			fh->SaveListCateg(list_category);//��������� ����� ������ ���������
		}
		else cout << "\n������ ��������� ������!\n";

		char buf[_MAX_PATH];
		GetCurrentDirectoryA(_MAX_PATH, buf);
		string path_dir = buf + path_category;

		string path_list = buf + path_category + "List.txt";//������ ���� � ������ ������ � ���������

		//�������� ������ ������ � ��������� ��� ������� ��������
		ifstream in(path_list);
		if (in.is_open())
		{
			string str_buf;
			while (!in.eof())
			{
				getline(in, str_buf);
				list_tests.push_back(str_buf);
			}
			list_tests.pop_back();
		}
		in.close();
		string tmp = path_dir;
		for (auto &el : list_tests)//������ ��� ����� � ��������
		{
			tmp += el + ".txt";
			int rez = remove(tmp.c_str());//�������� �����
			tmp = path_dir;
		}
		remove(path_list.c_str());//�������� ������ ������ 
		_rmdir(path_dir.c_str());//�������� ���������
		cout << "\n������� ������!\n";
		Sleep(1000);
	}
	system("cls");
}
//������� ��� ��������� ����� ������
void SetColor(int text, int background)  
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
//������ ���� ������
void Yellow()
{
	SetColor(YELLOW, BLACK);
}
//����� ���� ������
void White()
{
	SetColor(WHITE, BLACK);
}
//������� ���� ������
void Red()
{
	SetColor(RED, BLACK);
}
