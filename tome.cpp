#include "student.h"
#include <time.h>
#include <conio.h>
#include <windows.h>

const double interval = 0.5;

Student stu;

void refresh(int tim)
{
	Sleep(1000 * interval * tim);
	system("cls");
	cout << "---- 学生日程管理系统 v1.0 ----" << endl;
}

void subsave()
{
	cout << "正在保存信息..." << endl;
	stusave();
	cout << "保存成功！" << endl;
	system("pause");
	exit(0);
}

bool action(string &str)
{
	cout << str << endl;
	if(str == "save")
		subsave();
	cout << "check!" << endl;
	return false;
}

int login()
{
	int id = 1;
	string username, password;

	cout << "请输入用户名/学号: ";
	cin >> username;

	auto op = stus_dict.find(username);
	if(op==stus_dict.end())
		return -1;

	id = stus_dict[username];
	stu = stus[id];

	bool status = true;

	for (int wrong = 0; status; wrong++)
	{
		if (wrong > 0)
			cout << "密码错误！" << endl;
		cout << "请输入密码: ";
		cin >> password;
		if (stu.check(password))
			status = false;
	}
	return id;
}

void preload()
{
	cout << "正在载入地图信息..." << endl;
	mapinit();
	cout << "正在载入学生信息..." << endl;
	stuinit();
	cout << "开始模拟" << endl;
	refresh(2);

	for(int status = login(); status==-1; status = login());
	cout << "登陆成功！" << endl;
	refresh(2);
}

// nowtime
// nextday::today activity
// next time
// now action
// path

void timestart()
{
	while(true)
	{
		Tome now = {7, 22};
		auto atci = stu.getless();
		for(int i=1;i<=7;i++)
		{
			// loop(atci, now);
			cout << "今天日程已结束!" << endl;
			stu.rest();
 			cout << endl << "明天日程: ";
			stu.nextday(now.day); // 输出第二天日程

			for(int i=1;i<=24;i++)
			{
				if(kbhit())
				{
					bool op = true;
					while(op)
					{
						string order;
						cin >> order;
						op = action(order);
					}
				}
				now.putime(cout);
				Sleep(1000*interval*2);
				now.nextime();
				if(now.hour == atci->tome.hour)
				{
					// 判断acti类型
					atci->textout(cout);
					stu.move(atci->loca);
					atci++;
				}
			}
		}
	}
}

int main()
{
	preload();
	timestart();
	return 0;
}
