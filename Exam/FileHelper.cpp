#include "FileHelper.h"

FileHelper::FileHelper()
{
}

FileHelper::~FileHelper()
{
}
//возврат статического указателя(singleton)
FileHelper * FileHelper::GetInstance()
{
	static FileHelper * p = new FileHelper;
	return p;
}
//загрузка списка аккаунтов
void  FileHelper::LoadAccounts(vector<Account> & v)
{
	string path = "Accounts.dat";
	ifstream in(path, ios::in | ios::binary);
	if (in.is_open())
	{
		Account add;
		while (!in.eof())//загрузка всех юзеров
		{
			in >> add;
			v.push_back(add);
		}
		v.pop_back();
	}
	
	in.close();
}
//сохранение списка аккаунтов
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
//добавление в спискок новый аккаунт
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
//загрузка объекта пользователь
User FileHelper::LoadUser(string path)
{
	//загр юсера
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);
	string cur_path = buf;

	cur_path += "\\Users\\";//путь к каталогу всех пользователей
	
	cur_path += path;//путь к конкретному юсеру
	string name, surname, email, type;
	User tmp;
	ifstream in(cur_path+=".dat", ios::in | ios::out | ios::binary);//проверить моды
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
//сохравнение объекта пользователь
void FileHelper::SaveUser(User * user)
{
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);
	string path = buf;
	path += "\\Users\\";//путь к каталогу всех пользователей
	_mkdir(path.c_str());//если первый то создаем каталог
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
//нахождение теста и возврат его номера из списка
int FileHelper::FindTest(string path_category, vector<string> * list_tests)
{
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);
	string path_dir = buf + path_category;
	_mkdir(path_dir.c_str());//создали папку если надо

	string path_list = buf + path_category + "List.txt";//полный путь к списку

	//загрузка списка
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
	//показ списка для выбора теста
	unsigned int num = 1;
	Yellow();
	cout << "\n\tСписок тестов :\n";
	White();
	if (list_tests->size() == 0)//каталог пуст
	{
		Yellow();
		cout << "\n\n\tКаталог пуст!\n";
		White();
		num = 0;
		Sleep(1500);
		system("cls");
	}
	else //каталог не пуст
	{
		for (auto &el : *list_tests)//показ всех тестов из каталога
		{
			cout << "\n" << num << "." << el << "\n";
			++num;
		}
		cout << "\n";
		bool in_range = false;
		do {
			Yellow();
			cout << "Выберите номер теста : ";
			White();
			cin >> num;//выбор теста
			
			if (num >= 1 && num <= list_tests->size())
				in_range = true;
			else
			{
				Red();
				cout << "Неверно задан номер теста!\n";
				White();
			}
		} while (!in_range);
	}
	return num;//возврат номера выбраного теста
}
//проверка доступа ктесту
bool FileHelper::AccessToTest(string login, string name_test)
{
	bool access = true;
	bool first_try = true;
	vector<Visitors>vec;
	Visitors tmp;
	LoadTestVisitors(vec);//загрузка списка
	for (vector<Visitors>::iterator it = vec.begin(); it != vec.end(); ++it)//проверка доступа и на первое прохождение
	{
		if ((*it).name == login)
			if ((*it).test == name_test)//если тест уже проходился этим пользователем
			{
				first_try = false;
				if ((*it).num == 3)access = false;//если было три попытки - блокируется доступ
				else (*it).num++;//если меньше - то +1 попытка
			}
	}
	if (first_try)//если первое прохождение теста - делаем запись об этом
	{
		tmp.name = login;
		tmp.test = name_test;
		tmp.num = 1;
		vec.push_back(tmp);
	}
	SaveTestVisitors(vec);//сохраняем новый список
	return access;//возврат разрешения на прохождение
}
//загрузка списка пользователей,которые уже проходили тесты
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
				in >> tmp.name;//имяпользователя
				in >> tmp.num;//номер попытки
				in.ignore();
				getline(in, tmp.test, '\n');//название теста
				vec.push_back(tmp);
			} while (!in.eof());
			if (vec.size() >= 1)
				 vec.pop_back();
			in.close();
		}
	}
}
//сохранение списка пользователей,которые уже проходили тесты
void FileHelper::SaveTestVisitors(vector<Visitors>& vec)
{
	string cur_path = "Test_visitors.txt";
	ofstream out(cur_path, ios::out | ios::trunc);
	if (out.is_open())
	{
		for (auto &el : vec)
		{
			out << el.name << " ";//имяпользователя
			out << el.num << " ";//номер попытки
			out << el.test << "\n";//название теста
		}
		out.close();
	}
	else
		cerr << "Ошибка записи посетителей теста\n";
}
//загрузка теста
void FileHelper::LoadTest(Test & test,string path_category)
{
	//загружаем список тестов для выбора
	vector<string>list_tests;
	int num = FindTest(path_category, &list_tests);//номер теста из подкаталога
	if (num)
	{//загрузка теста
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
			cerr << "Тест не загрузился\n";
			White();
			Sleep(1500);
		}
	}
}
//сохранение теста
void FileHelper::SaveTest(Test & test,string path_category)
{
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);

	string path = buf + path_category + test.GetNameTest()+".txt";//путь к тесту
	ofstream out(path, ios::out);
	if (out.is_open())
	{
		out << test;
		Yellow();
		cout << "\t\tТест сохранен!!!\n";
		White();
		Sleep(1000);
	}
	else
	{
		Red();
		cerr << "Ошибка сохранения теста\n";
		White();
	}
	out.close();

}
//сохранение списка тестов в каталоге
void FileHelper::SaveListTest(string full_path, vector<string>& vect)
{
	ofstream out(full_path, ios::out);//сохраняем новый список тестов
	if (out.is_open())
	{
		for (unsigned int i = 0; i < vect.size(); ++i)
			out << vect[i] << "\n";
		Yellow();
		cout << "Спиcок сохранен\n";
		White();
	}
	else
		cerr << "Не открылся список тестов для сохранения\n";
	out.close();
}
//загрузка списка категорий тестов
bool FileHelper::LoadListCateg(vector<string>& List_categories)//потестить
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
		cerr << "\nОшибка загрузки списка категорий\n";
	return false;
}
//сохранение списка категорий тестов
void FileHelper::SaveListCateg(vector<string>& List_categories)//потестить
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
		cerr << "\nОшибка сохранения списка категорий\n";
	out.close();
}
//создание каталога (для новой категории)
void FileHelper::CreateDirect(string path)
{
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);
	string path_dir = buf;
	path_dir += "\\Tests\\";
	path_dir += "\\" + path + "\\";
	_mkdir(path_dir.c_str());
}

