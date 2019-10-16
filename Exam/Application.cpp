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
	if (user->GetAccess())//проверка доступа входа в программу
		do {
			do {
				system("cls");
				Yellow();cout << "\n\n\t\t\tМЕНЮ\n\n\n\t1 - "; White();
				cout << "Выбрать тест";
				Yellow(); cout << "\n\n\t2 - "; White(); cout << "Статистика";
				Yellow(); cout << "\n\n\t0 - "; White(); cout << "Выход\n";
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
				SelectCategory(path_category);//выбор категории тестов
				OpenTest(path_category, *user);//открытие теста
				system("cls");
			}
			else
			{//показ статистики
				system("cls");
				user->ShowStatistic();
			}

			do {
				Yellow();
				cout << "\n\n\n\t\tПродолжить работу?\n";
				White();
				cout << "\t1 - Да\n"
					<< "\t2 - Нет\n";
				cin >> choice;
			} while (choice != 1 && choice != 2);
			if (choice == 2)
			{//выход из программы
				fh->SaveUser(user);
				exit(0);
			}
			system("cls");
		} while (true);
	else
	{
		Red();
		cout << "\n\n\n\tВаш аккаунт заблокирован.Обратитесь к администратору!\n\n";
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
	if (user->GetAccess())//проверка доступа входа в программу
	{
		do {
			do {
				Yellow(); cout << "\n\n\t\t\tМЕНЮ(преподователь)\n\n\n\t1 - "; White(); cout << "Добавить тест";
				Yellow(); cout << "\n\n\t2 - "; White(); cout << "Удалить тест";
				Yellow(); cout << "\n\n\t3 - "; White(); cout << "Редактировать тест";
				Yellow(); cout << "\n\n\t4 - "; White(); cout << "Разблокировать доступ к тесту";
				Yellow(); cout << "\n\n\t5 - "; White(); cout << "Добавить категорию";
				Yellow(); cout << "\n\n\t6 - "; White(); cout << "Удалить категорию";
				Yellow(); cout << "\n\n\t0 - "; White(); cout << "Выход\n";
				cin >> choice;
				if (choice == 0)exit(0);
			} while (choice < 1 && choice > 6);
			if (choice >= 1 && choice <= 3)
			{
				string path_category="\\Tests\\";
				if (choice >= 1 && choice <= 3)
					SelectCategory(path_category);//выбор категории тестов
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
		cout << "\n\n\n\tВаш аккаунт заблокирован.Обратитесь к администратору!\n\n";
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
			Yellow(); cout << "\n\n\t\t\tМЕНЮ(администратор)\n\n\n\t1 - "; White(); cout << "Добавить пользователя(преподователя)";
			Yellow(); cout << "\n\n\t2 - "; White(); cout << "Добавить тест";
			Yellow(); cout << "\n\n\t3 - "; White(); cout << "Удалить тест";
			Yellow(); cout << "\n\n\t4 - "; White(); cout << "Редактировать тест";
			Yellow(); cout << "\n\n\t5 - "; White(); cout << "Изменить доступ пользователю";
			Yellow(); cout << "\n\n\t6 - "; White(); cout << "Изменить данные входа в систему";
			Yellow(); cout << "\n\n\t0 - "; White(); cout << "Выход\n";
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
			SelectCategory(path_category);//выбор категории тестов
			if (path_category != "\\Tests\\")
			{
				switch (choice)//работа с тестом
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
// + одна дополнительная попытка
void Application::UnLockUser()
{
	FileHelper * fh = FileHelper::GetInstance();
	vector<Visitors> vec;
	string name, surname, test_name,test;
	fh->LoadTestVisitors(vec);//загрузка списка студентов проходивших тесты
	system("cls");
	Yellow();
	cout << "\n\n\n\n\t\tДанные для разблокировки";
	White();
	cout << "\n\n\tИмя     : ";
	cin >> name;
	cout << "\n\tФамилия : ";
	cin >> surname;
	cout << "\n\tНазвание теста :";
	cin.ignore();
	getline(cin, test_name);
	test = test_name;
	
	vector<Visitors>::iterator it;
	it = find_if(vec.begin(), vec.end(), [name,surname,test](Visitors stud)//поиск студента по введенным данным
	{
		return stud.name == (name + surname) && stud.test == test;
	});
	if (it != vec.end())//если найден
	{
		int choice;
		do {
			Yellow();
			cout << "\nРазблокировать доступ студенту " << name << " " << surname << " к тесту \"" << test_name << "\"?\n";
			White();
			cout << "\n1 - Да\n"
				 << "2 - Нет\n\n";
			cin >> choice;
		} while (choice != 1 && choice != 2);
		if (choice == 1)
		{
			(*it).num--;//одна дополнительная попытка
			Yellow();
			cout << "\nДоступ разблокирован!\n";
			White();
			Sleep(1000);
			system("cls");
		}
		fh->SaveTestVisitors(vec);
	}
	else
	{
		Red();
		cout << "\n\tНе найден\n";
		Sleep(1000);
		White();
	}
	system("cls");
}
//редактирование теста
void Application::EditTest(string path_category)
{
	FileHelper * fh = FileHelper::GetInstance();
	Test test;
	fh->LoadTest(test, path_category);//загрузка теста
	if (test.GetNameTest() != "")
		test.EditTest(path_category);//редактирование теста
}
//показ теста
void Application::OpenTest(string path_category, User & user)
{
	FileHelper * fh = FileHelper::GetInstance();
	Test test;
	fh->LoadTest(test, path_category);//загрузка теста
	if (test.GetNameTest() != "")//проверка что тест загрузился
		if (fh->AccessToTest((user.GetName() + user.GetSurname()), test.GetNameTest()))//проверка доступа студента к тесту
			test.Show(user);
		else
		{
			Red();
			cout << "\n\n\n\tТест заблокирован.Обратитесь к препадователю.\n";
			White();
			Sleep(1500);
		}
}
//добавление теста
void Application::AddTest(string path_category)
{
	FileHelper * fh = FileHelper::GetInstance();
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);
	string path_dir = buf + path_category;
	_mkdir(path_dir.c_str());//создали папку если надо

	//создаем тест
	system("cls");
	int amount_questions;
	Yellow();
	cout << "Введите количество вопросов :";
	White();
	cin >> amount_questions;
	Test new_test(amount_questions);
	//сохраняем тест
	fh->SaveTest(new_test, path_category);
	//добавляем в список тестов подкаталога
	ofstream out(path_dir + "List.txt", ios::app);
	if (out.is_open())
		out << new_test.GetNameTest() << "\n";
	else
		cerr << "Не открылся список тестов\n";
	out.close();
	system("cls");
}
//удаление теста
void Application::DeleteTest(string path_category)
{
	FileHelper * fh = FileHelper::GetInstance();
	char buf[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, buf);

	vector<string>  list_tests;
	//находим нужный тест
	int num_test = fh->FindTest(path_category, &list_tests);
	
	if (num_test)//если нужный тест найден
	{
		string path_test = buf + path_category + list_tests[num_test - 1] + ".txt";
		if (remove(path_test.c_str()) != 0)//удаление теста
			cerr << "\nОшибка удаления теста.\n";
		else
		{
			Yellow();
			cout << "Тест удален успешно\n";
			White();
			vector<string>::iterator it = list_tests.begin();
			//удаляем запись из списка тестов
			list_tests.erase(it + (num_test - 1));
			//сохраняем обновленный список
			fh->SaveListTest(buf + path_category + "List.txt", list_tests);
		}
		Sleep(1500);
		system("cls");
	}
}
//выбор категории тестов
void Application::SelectCategory(string & path_category)
{
	FileHelper *fh = FileHelper::GetInstance();
	vector<string> list_cat;
	system("cls");
	//загрузка списка существующих категорий
	fh->LoadListCateg(list_cat);
	if (list_cat.size() != 0)//если список не пустой
	{
		Yellow();
		cout << "\n\tВыберите категорию :\n\n";
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
		cout << "Вернутся в главное меню\n";
		do {
			Yellow();
			cout << "\n\tНомер : ";
			White();
			cin >> choice;
		} while (choice<0 || choice>list_cat.size());
		if (choice == 0)return;
		path_category += list_cat[choice - 1] + "\\";
	}
	else
	{//если список пустой
		cout << "\nСписок категорий пустой!\n";
		//добавляем категорию
		AddCategory();
		//загружаем обновленный список категорий
		vector<string> List_categories;
		fh->LoadListCateg(List_categories);
		//формирум путь к категории для возврата
		path_category += List_categories[0] + "\\";
	}
}
//функция редактирования личных данных(только для администратора)
void Application::EditData(User & user)
{
	user.SetName();
	user.SetSurname();
	user.SetEmail();
}
//показ всех аккаунтов для просмотра доступа в систему (только для администратора)
void Application::ShowAccounts(vector<Account> & vec)
{
	system("cls");
	//сортируем по фамилии 
	sort(vec.begin(), vec.end(), [](Account a, Account b) {
		return a.GetSurname() < b.GetSurname();
	});
	if (vec.size())
	{
		Yellow();
		cout << "\n\n\tСписок аккаунтов\n";
		White();
		int i = 1;
		for (auto &el : vec)
		{
			cout << "\n"<<i<<") " <<setw(15) << left <<el.GetSurname() << setw(15) << left << el.GetName() <<"'"<< setw(15) << left << el.GetType()+"'";
			if (el.GetAccess())
			{
				Yellow();
				cout << "разрешен";
				White();
			}
			else
			{
				Red();
				cout << "заблокирован";
				White();
			}
			++i;
		}
	}
	else
		cout << "\nНе зарегестрировано ни одного пользователя!\n";
	cout << "\n";
}
//изменение доступа в систему (только для администратора)
void Application::ChangeAccess()
{
	FileHelper *fh = FileHelper::GetInstance();
	vector<Account> vec;
	int num_acc = 0;
	//загрузка всех аккаунтов
	fh->LoadAccounts(vec);
	//показ всех аккаунтов
	ShowAccounts(vec);
	//выбор аккаунта
	do {
		Yellow();
		cout << "\nВведите номер аккаунта чтобы изменить доступ : ";
		White();
		cin >> num_acc;
	} while (num_acc < 1 || num_acc > vec.size());
	if (vec[num_acc - 1].GetAccess())//изменение доступа
		vec[num_acc - 1].SetAccess(false);
	else vec[num_acc - 1].SetAccess(true);
	Yellow();
	cout << "\nДоступ изменен!\n";
	White();
	fh->SaveAccounts(vec);//сохранение обновленного списка
	Sleep(1000);
	system("cls");
}
//добавление категории тестов
void Application::AddCategory()
{
	FileHelper * fh = FileHelper::GetInstance();
	vector<string> List_categories;
	string name_category;
	bool is_load;//для проверки загрузился список или нет
	//загрузка списка категории
	is_load = fh->LoadListCateg(List_categories);
	if (is_load)
	{//добавление категории
		Yellow();
		cout << "\nВведите название новой категории : ";
		White();
		cin.ignore();
		getline(cin, name_category);
		vector<string>::iterator it;
		//ищем существует ли такая же категория
		it = find_if(List_categories.begin(), List_categories.end(), [name_category] (string str) {return name_category == str;});

		if (it == List_categories.end())//если нет
		{
			List_categories.push_back(name_category);//добавляем в список новую категорию
			fh->CreateDirect(name_category);//создаем каталог
			fh->SaveListCateg(List_categories);//сохраняем новый список категорий
			Yellow();
			cout << "\nКатегория добавлена успешно!";
			White();
			Sleep(1000);
			system("cls");
		}
		else
		{
			Red();
			cout << "\nКатегория с таким названием уже существует!\n";
			White();
		}
	}
	else
	{
		cerr << "\nОшибка загрузки списка категорий\n";
	}
}
//удаление категории
void Application::DelCategory()
{
	FileHelper * fh = FileHelper::GetInstance();
	string path_category = "\\Tests\\";
	int choice;
	do {//предупреждение пользователя
		system("cls");
		Red();
		cout << "\n\n\t\tУдаление\n\n"
			<< "\tВсе содержимое каталога будет удалено !\n\n";
		White();
		cout << "1 - Продолжить\n"
			<< "2 - Отменить\n";
		cin >> choice;
	} while (choice != 1 && choice != 2);
	White();
	if (choice == 1)//продолжаем удаление
	{
		vector<string>list_tests;
		vector<string>list_category;
		//загрузка списка категорий
		fh->LoadListCateg(list_category);
		//выбор удаляемой категории
		if (list_category.size() != 0)
		{
			Yellow();
			cout << "\n\tВыберите категорию :\n\n";
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
				cout << "\n\tНомер : ";
				White();
				cin >> choice;
			} while (choice<1 || choice>list_category.size());
			vector<string>::iterator it = list_category.begin();
			path_category += list_category[choice - 1] + "\\";//путь к удаляемому каталогу
			list_category.erase(it + (choice - 1));//удаляем из списка категори
			fh->SaveListCateg(list_category);//сохраняем новый список категорий
		}
		else cout << "\nСписок категорий пустой!\n";

		char buf[_MAX_PATH];
		GetCurrentDirectoryA(_MAX_PATH, buf);
		string path_dir = buf + path_category;

		string path_list = buf + path_category + "List.txt";//полный путь к списку тестов в категории

		//загрузка списка тестов в категории для очистки каталога
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
		for (auto &el : list_tests)//удалил все тесты в каталоге
		{
			tmp += el + ".txt";
			int rez = remove(tmp.c_str());//удаление теста
			tmp = path_dir;
		}
		remove(path_list.c_str());//удаление самого списка 
		_rmdir(path_dir.c_str());//удаление категории
		cout << "\nКаталог удален!\n";
		Sleep(1000);
	}
	system("cls");
}
//функция для изменения цвета текста
void SetColor(int text, int background)  
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
//желтый цвет текста
void Yellow()
{
	SetColor(YELLOW, BLACK);
}
//белый цвет текста
void White()
{
	SetColor(WHITE, BLACK);
}
//красный цвет текста
void Red()
{
	SetColor(RED, BLACK);
}
