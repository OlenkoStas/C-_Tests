#include "Door.h"

Door::Door()
{
}
Door::~Door()
{
}
//���� � �������
User  Door::EntryMenu() 
{
	int choice = 0;
	do {
		system("cls");
		Yellow();
		cout << "\n\n\t\t����\n\n";
		cout << "\t[1]";
		White();
		cout << " �����������\n";
		Yellow();
		cout << "\t[2]";
		White();
		cout << " �����������\n";
		Yellow();
		cout << "\t[3]";
		White();
		cout << " �����\n";
		cin >> choice;
		if (choice == 3)exit(0);
	} while (choice != 1 && choice != 2);

	if (choice == 1)//�����������
	{
		return Avtorization();
	}
	else if (choice == 2)//�����������
	{
		return Registration();
	}
}
//�����������
User  Door::Avtorization()
{
	FileHelper *p = FileHelper::GetInstance();
	//�������� ������
	vector<Account> v;
	p->LoadAccounts(v);//�������� ������ ���������

	if (v.size() == 0)//���� ������ ������ ��������� - ������� ������ ������ � ������� Tests
		FirstLoad(p, v);
	//�����������
	string name, surname;
	do {
		system("cls");
		Yellow();
		cout << "\n\n\t\t�����������\n";
		White();
		cout << "\n\n\t���     : ";
		cin >> name;
		cout << "\n\t������� : ";
		cin >> surname;
		system("cls");
		//����� ������������ � ������ ���������
		vector<Account>::iterator it = find_if(v.begin(), v.end(), [name, surname](Account acc) {
			return name == acc.GetName() && surname == acc.GetSurname();
		});
		if (it == v.end())
		{
			cout << "������������ �� ������\n";
			Sleep(700);
		}
		else
		{//���� ������ �� ��������� � ����������
			string path = name + surname;
			User user = p->LoadUser(path);
			if (user.GetAccess() != (*it).GetAccess())//����� ��� ��������� �������,����� ������������� ��������(���� ����� ���� ������ ������������ ��� ������������� �������)
				user.SetAccess((*it).GetAccess());
			return user;
		}
	} while (true);
}
//�����������
User  Door::Registration()
{
	FileHelper *p = FileHelper::GetInstance();
	//�������� ������
	vector<Account> v;
	//�������� ������ ���������
	p->LoadAccounts(v);

	if (v.size() == 0)//���� ������ ������ ��������� - ������� ������ ������ � ������� Tests
		FirstLoad(p, v);
	//�����������
	string name, surname, email, type;
	do {
		system("cls");
		Yellow();
		cout << "\n\n\t\t�����������";
		White();
		cout << "\n\n\t���     : ";
		cin >> name;
		cout << "\n\t������� : ";
		cin >> surname;
		//����� ������������ � ������ ���������
		vector<Account>::iterator it = find_if(v.begin(), v.end(), [name, surname](Account acc) {
			return name == acc.GetName() && surname == acc.GetSurname();
		});
		if (it != v.end())
		{//���� ����� ��� ���� - �� ������
			cout << "������������ � ������ ������� ��� ����������.\n";
			Sleep(700);
		}
		else
		{
			cout << "\n\tEmail  : ";
			cin >> email;
			type = "user";
			//�������� ��������
			Account add(name, surname, email, type);
			//������ � ������ ���������
			v.push_back(add);
			//���������� ������ ������
			p->SaveAccounts(v);
			//������� �������
			return User(add);
		}
	} while (true);
}
// ���� ������ ������ ��������� - ������� ������ ������ � ������� ����� ��� ������
void Door::FirstLoad(FileHelper * p,vector<Account> & vec)
{
	Account admin("Admin", "Admin", "mail", "admin");
	User add(admin);
	p->SaveUser(&add);//��������� ������ ������������
	vec.push_back(admin);//��������� � ������ ���������
	p->SaveAccounts(vec);//��������� ������ ���������

	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);
	string path_dir = buf;
	path_dir += "\\Tests\\";
	_mkdir(path_dir.c_str());//������� ������� Tests

}


