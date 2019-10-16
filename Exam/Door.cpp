#include "Door.h"

Door::Door()
{
}
Door::~Door()
{
}
//вход в систему
User  Door::EntryMenu() 
{
	int choice = 0;
	do {
		system("cls");
		Yellow();
		cout << "\n\n\t\tВход\n\n";
		cout << "\t[1]";
		White();
		cout << " Авторизация\n";
		Yellow();
		cout << "\t[2]";
		White();
		cout << " Регистрация\n";
		Yellow();
		cout << "\t[3]";
		White();
		cout << " Выход\n";
		cin >> choice;
		if (choice == 3)exit(0);
	} while (choice != 1 && choice != 2);

	if (choice == 1)//авторизация
	{
		return Avtorization();
	}
	else if (choice == 2)//регистрация
	{
		return Registration();
	}
}
//авторизация
User  Door::Avtorization()
{
	FileHelper *p = FileHelper::GetInstance();
	//загрузка данных
	vector<Account> v;
	p->LoadAccounts(v);//загрузка списка аккаунтов

	if (v.size() == 0)//если первый запуск программы - создаем учетку админа и каталог Tests
		FirstLoad(p, v);
	//авторизация
	string name, surname;
	do {
		system("cls");
		Yellow();
		cout << "\n\n\t\tАвторизация\n";
		White();
		cout << "\n\n\tИмя     : ";
		cin >> name;
		cout << "\n\tФамилия : ";
		cin >> surname;
		system("cls");
		//поиск пользователя в списке аккаунтов
		vector<Account>::iterator it = find_if(v.begin(), v.end(), [name, surname](Account acc) {
			return name == acc.GetName() && surname == acc.GetSurname();
		});
		if (it == v.end())
		{
			cout << "Пользователь не найден\n";
			Sleep(700);
		}
		else
		{//если найден то загружаем и возвращаем
			string path = name + surname;
			User user = p->LoadUser(path);
			if (user.GetAccess() != (*it).GetAccess())//нужно для изменения доступа,после разблокировки аккаунта(если перед этим входом пользователь был разблокирован админом)
				user.SetAccess((*it).GetAccess());
			return user;
		}
	} while (true);
}
//регистрация
User  Door::Registration()
{
	FileHelper *p = FileHelper::GetInstance();
	//загрузка данных
	vector<Account> v;
	//загрузка списка аккаунтов
	p->LoadAccounts(v);

	if (v.size() == 0)//если первый запуск программы - создаем учетку админа и каталог Tests
		FirstLoad(p, v);
	//регистрация
	string name, surname, email, type;
	do {
		system("cls");
		Yellow();
		cout << "\n\n\t\tРегистрация";
		White();
		cout << "\n\n\tИмя     : ";
		cin >> name;
		cout << "\n\tФамилия : ";
		cin >> surname;
		//поиск пользователя в списке аккаунтов
		vector<Account>::iterator it = find_if(v.begin(), v.end(), [name, surname](Account acc) {
			return name == acc.GetName() && surname == acc.GetSurname();
		});
		if (it != v.end())
		{//если такой уже есть - то заново
			cout << "Пользователь с такими данными уже существует.\n";
			Sleep(700);
		}
		else
		{
			cout << "\n\tEmail  : ";
			cin >> email;
			type = "user";
			//создание аккаунта
			Account add(name, surname, email, type);
			//запись в список аккаунтов
			v.push_back(add);
			//сохранение нового списка
			p->SaveAccounts(v);
			//возврат объекта
			return User(add);
		}
	} while (true);
}
// если первый запуск программы - создаем учетку админа и создаем папку для тестов
void Door::FirstLoad(FileHelper * p,vector<Account> & vec)
{
	Account admin("Admin", "Admin", "mail", "admin");
	User add(admin);
	p->SaveUser(&add);//сохраняем объект пользователь
	vec.push_back(admin);//добавляем в список аккаунтов
	p->SaveAccounts(vec);//сохраняем список аккаунтов

	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);
	string path_dir = buf;
	path_dir += "\\Tests\\";
	_mkdir(path_dir.c_str());//создаем каталог Tests

}


