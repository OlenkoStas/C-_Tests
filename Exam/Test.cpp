#include "Test.h"


Test::Test()
{
	
}
//конструктор создаем тест
Test::Test(int amount_questions)
{
	this->amount_questions = amount_questions;
	for (int i = 0; i < this->amount_questions; ++i)
	{
		this->test.push_back((*new Question()));
	}
	cin.ignore();
	Yellow();
	cout << "Введите название теста :";
	White();
	getline(cin, name_test);
}

Test::~Test()
{
}
//возвращает имя теста
string Test::GetNameTest()
{
	return name_test;
}
//показ теста(при прохождении и редактировании)
void Test::Show(User & user) 
{
	if (this->test.size())
	{
		int my_answer = 0;//ответ пользователя
		int right_answers = 0;//кол-во правельных ответов
		int num_question = 1;//ноиер вопроса
		for (auto &el : test)
		{
			int right_answ;
			cout << "\nВопрос ";
			cout << num_question << " :\n";
			right_answ = el.ShowQuestion();
			Yellow();
			cout << "\n\tОтвет : ";
			White();
			cin >> my_answer;
			if (my_answer == right_answ)
				++right_answers;
			++num_question;
			system("cls");
		}
		Yellow();
		cout << "\n\n\n\t\tТест окончен.\n";
		White();
		Sleep(1000);
		//вычисление результата в процентах
		int rez = ((double)right_answers / (double)this->amount_questions) * 100;
		cout << "\n\tКоличество правельных ответов : ";
		Yellow();
		cout << rez << " %\n";
		White();
		Sleep(1500);
		//добавляем запись в статистику пользователя
		if (user.GetType() == "user")
			user.AddStat(this->name_test, rez);
		system("cls");
	}
}
//редактирование теста
void Test::EditTest(string path_cat)
{
	FileHelper * fh = FileHelper::GetInstance();
	int choice = 0;
	bool is_continue = true;
	do {
		do {//подменю
			system("cls");
			Yellow();
			cout << "\n\t\tРедактирование теста \""<<this->name_test<<"\"\n";
			White();
			cout << "\n1 - Добавить вопрос\n"
				<< "\n2 - Редактировать существующие\n"
				<< "\n3 - Закончить  и сохранить\n"
				<< "\n4 - Отменить\n\n";
			cin >> choice;
		} while (choice < 1 && choice>4);
		if (choice == 1)
		{//добавление вопроса
			Question add(1);
			add.SetQuestion();//создаем вопрос
			this->amount_questions++;
			this->test.push_back(add);//добавляем в конец теста
			cout << "\nВопрос добавлен!\n";
			Sleep(1000);
		}
		else if (choice == 2)
		{//Редактировать существующие
			for (auto &el:this->test)
			{
				el.ShowQuestion();//показ вопроса
				do {//выбор действия
					Yellow();
					cout << "\n1";
					White();
					cout << "- редактировать\n";
					Yellow();
					cout << "2";
					White();
					cout << "- перейти на следующий вопрос.\n";
					cin >> choice;
				} while (choice != 1 && choice != 2);
				if (choice == 2)continue;
				el.SetQuestion();//если редактировать - перезаписуем существующий вопрос
			}
			Yellow();
			cout << "\n\tРедактирование завершено успешно!\n";
			White();
			Sleep(1000);
		}
		else if (choice == 3)
		{//сохраняем изменения
			fh->SaveTest(*this, path_cat);
			is_continue = false;
		}
		else
		{//отмена
			cout << "\nРедактирование отменено!";
			is_continue = false;
			Sleep(1000);
		}
	} while (is_continue);
	system("cls");
}
//для вывода в файл
ostream & operator<<(ostream & out, Test & obj)
{
	out << obj.name_test << "\n";
	out << obj.amount_questions << " ";
	
	for (auto &el : obj.test)
	     out << el ;
	return out;
}
//для ввода из файла
istream & operator>>(istream & in, Test & obj)
{

	getline(in, obj.name_test);
	in >> obj.amount_questions ;
	
	Question q(0);
	string str;
	
	while (!in.eof())
	{
		in >> q;
		obj.test.push_back(q);
	}
	obj.test.pop_back();
	return in;
}
