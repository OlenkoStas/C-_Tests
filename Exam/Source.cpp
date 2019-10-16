#include"Application.h"
#include"User.h"
#include"Door.h"


int main()
{
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Door * p = Door::PointDoor();
	Application * app = Application::GetInstance();

	User  user = p->EntryMenu();//возвращает найденого или нового юзера
	//вызов меню для каждого пользователя
	if (user.GetType() == "user")
		app->UserMenu(&user);
	else if (user.GetType() == "teacher")
		app->TeacherMenu(&user);
	else if (user.GetType() == "admin")
		app->AdminMenu(&user);
	return 0;
}
