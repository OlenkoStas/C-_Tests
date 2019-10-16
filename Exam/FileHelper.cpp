#include "FileHelper.h"

FileHelper::FileHelper()
{
}

FileHelper::~FileHelper()
{
}
//������� ������������ ���������(singleton)
FileHelper * FileHelper::GetInstance()
{
	static FileHelper * p = new FileHelper;
	return p;
}
//�������� ������ ���������
void  FileHelper::LoadAccounts(vector<Account> & v)
{
	string path = "Accounts.dat";
	ifstream in(path, ios::in | ios::binary);
	if (in.is_open())
	{
		Account add;
		while (!in.eof())//�������� ���� ������
		{
			in >> add;
			v.push_back(add);
		}
		v.pop_back();
	}
	
	in.close();
}
//���������� ������ ���������
void FileHelper::SaveAccounts(vector<Account> & v)
{
	string path = "Accounts.dat";
	ofstream out(path, ios::out | ios::trunc | ios::binary);
	if (out.is_open())
	{
		for (auto &el : v)
			out << el;
		out.close();
	}
	else cerr << "Error,file not saved\n";
}
//���������� � ������� ����� �������
void FileHelper::AddAccount(Account * acc)
{
	string path = "Accounts.dat";
	ofstream out(path, ios::app | ios::out | ios::binary);
	if (out.is_open())
	{
		out << *acc;
	}
	else cerr << "Error,file not saved\n";
}
//�������� ������� ������������
User FileHelper::LoadUser(string path)
{
	//���� �����
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);
	string cur_path = buf;

	cur_path += "\\Users\\";//���� � �������� ���� �������������
	
	cur_path += path;//���� � ����������� �����
	string name, surname, email, type;
	User tmp;
	ifstream in(cur_path+=".dat", ios::in | ios::out | ios::binary);//��������� ����
	if (in.is_open())
	{
		in >> tmp;
	}
	else
	{
		cerr << "Error.File user is not loaded.\n";
	}
	in.close();
	
	return tmp;
}
//����������� ������� ������������
void FileHelper::SaveUser(User * user)
{
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);
	string path = buf;
	path += "\\Users\\";//���� � �������� ���� �������������
	_mkdir(path.c_str());//���� ������ �� ������� �������
	path+=user->GetName() + user->GetSurname();
	ofstream out(path +=".dat", ios::out | ios::trunc | ios::binary);
	if (out.is_open())
	{
		out << *user;
	}
	else
		cerr << "Error.File is not saved.";
	out.close();
}
//���������� ����� � ������� ��� ������ �� ������
int FileHelper::FindTest(string path_category, vector<string> * list_tests)
{
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);
	string path_dir = buf + path_category;
	_mkdir(path_dir.c_str());//������� ����� ���� ����

	string path_list = buf + path_category + "List.txt";//������ ���� � ������

	//�������� ������
	ifstream in(path_list);
	if (in.is_open())
	{
		string str_buf;
		while (!in.eof())
		{
			getline(in, str_buf);
			list_tests->push_back(str_buf);
		}
		list_tests->pop_back();
	}
	in.close();
	//����� ������ ��� ������ �����
	unsigned int num = 1;
	Yellow();
	cout << "\n\t������ ������ :\n";
	White();
	if (list_tests->size() == 0)//������� ����
	{
		Yellow();
		cout << "\n\n\t������� ����!\n";
		White();
		num = 0;
		Sleep(1500);
		system("cls");
	}
	else //������� �� ����
	{
		for (auto &el : *list_tests)//����� ���� ������ �� ��������
		{
			cout << "\n" << num << "." << el << "\n";
			++num;
		}
		cout << "\n";
		bool in_range = false;
		do {
			Yellow();
			cout << "�������� ����� ����� : ";
			White();
			cin >> num;//����� �����
			
			if (num >= 1 && num <= list_tests->size())
				in_range = true;
			else
			{
				Red();
				cout << "������� ����� ����� �����!\n";
				White();
			}
		} while (!in_range);
	}
	return num;//������� ������ ��������� �����
}
//�������� ������� ������
bool FileHelper::AccessToTest(string login, string name_test)
{
	bool access = true;
	bool first_try = true;
	vector<Visitors>vec;
	Visitors tmp;
	LoadTestVisitors(vec);//�������� ������
	for (vector<Visitors>::iterator it = vec.begin(); it != vec.end(); ++it)//�������� ������� � �� ������ �����������
	{
		if ((*it).name == login)
			if ((*it).test == name_test)//���� ���� ��� ���������� ���� �������������
			{
				first_try = false;
				if ((*it).num == 3)access = false;//���� ���� ��� ������� - ����������� ������
				else (*it).num++;//���� ������ - �� +1 �������
			}
	}
	if (first_try)//���� ������ ����������� ����� - ������ ������ �� ����
	{
		tmp.name = login;
		tmp.test = name_test;
		tmp.num = 1;
		vec.push_back(tmp);
	}
	SaveTestVisitors(vec);//��������� ����� ������
	return access;//������� ���������� �� �����������
}
//�������� ������ �������������,������� ��� ��������� �����
void FileHelper::LoadTestVisitors(vector<Visitors>& vec)
{
	string cur_path = "Test_visitors.txt";
	Visitors tmp;
	ifstream in(cur_path, ios::in);
	{
		if (in.is_open())
		{
			do
			{
				in >> tmp.name;//���������������
				in >> tmp.num;//����� �������
				in.ignore();
				getline(in, tmp.test, '\n');//�������� �����
				vec.push_back(tmp);
			} while (!in.eof());
			if (vec.size() >= 1)
				 vec.pop_back();
			in.close();
		}
	}
}
//���������� ������ �������������,������� ��� ��������� �����
void FileHelper::SaveTestVisitors(vector<Visitors>& vec)
{
	string cur_path = "Test_visitors.txt";
	ofstream out(cur_path, ios::out | ios::trunc);
	if (out.is_open())
	{
		for (auto &el : vec)
		{
			out << el.name << " ";//���������������
			out << el.num << " ";//����� �������
			out << el.test << "\n";//�������� �����
		}
		out.close();
	}
	else
		cerr << "������ ������ ����������� �����\n";
}
//�������� �����
void FileHelper::LoadTest(Test & test,string path_category)
{
	//��������� ������ ������ ��� ������
	vector<string>list_tests;
	int num = FindTest(path_category, &list_tests);//����� ����� �� �����������
	if (num)
	{//�������� �����
		char buf[_MAX_PATH];
		GetCurrentDirectoryA(_MAX_PATH, buf);
		string path_test = buf+ path_category + list_tests[num - 1] + ".txt";
		ifstream in(path_test);
		if (in.is_open())
		{
			in >> test;
			system("cls");
			in.close();
		}
		else
		{
			Red();
			cerr << "���� �� ����������\n";
			White();
			Sleep(1500);
		}
	}
}
//���������� �����
void FileHelper::SaveTest(Test & test,string path_category)
{
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);

	string path = buf + path_category + test.GetNameTest()+".txt";//���� � �����
	ofstream out(path, ios::out);
	if (out.is_open())
	{
		out << test;
		Yellow();
		cout << "\t\t���� ��������!!!\n";
		White();
		Sleep(1000);
	}
	else
	{
		Red();
		cerr << "������ ���������� �����\n";
		White();
	}
	out.close();

}
//���������� ������ ������ � ��������
void FileHelper::SaveListTest(string full_path, vector<string>& vect)
{
	ofstream out(full_path, ios::out);//��������� ����� ������ ������
	if (out.is_open())
	{
		for (unsigned int i = 0; i < vect.size(); ++i)
			out << vect[i] << "\n";
		Yellow();
		cout << "���c�� ��������\n";
		White();
	}
	else
		cerr << "�� �������� ������ ������ ��� ����������\n";
	out.close();
}
//�������� ������ ��������� ������
bool FileHelper::LoadListCateg(vector<string>& List_categories)//���������
{
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);
	string path = buf;
	path += "\\Tests\\";
	path += "ListCateg.txt";
	ifstream in(path, ios::in | ios::out | ios::app);
	if (in.is_open())
	{
		string buffer;
		while (!in.eof())
		{
			getline(in, buffer);
			List_categories.push_back(buffer);
		}
		List_categories.pop_back();
		in.close();
		return true;
	}
	else
		cerr << "\n������ �������� ������ ���������\n";
	return false;
}
//���������� ������ ��������� ������
void FileHelper::SaveListCateg(vector<string>& List_categories)//���������
{
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);
	string path = buf;
	path += "\\Tests\\";
	path += "ListCateg.txt";
	ofstream out(path, ios::out);
	if (out.is_open())
	{
		for (auto &el : List_categories)
		{
			out << el <<"\n";
		}
	}
	else
		cerr << "\n������ ���������� ������ ���������\n";
	out.close();
}
//�������� �������� (��� ����� ���������)
void FileHelper::CreateDirect(string path)
{
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);
	string path_dir = buf;
	path_dir += "\\Tests\\";
	path_dir += "\\" + path + "\\";
	_mkdir(path_dir.c_str());
}

