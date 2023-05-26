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
	if(str == "error")
	{
		cout << "error" << endl;
		return false;
	}
	if(str == "find")
	{
		cout << "kind of find: ";
		cin >> str;
		if(str == "name")
		{
			cin >> str;
			auto res = stu.find_acti(str);
			res->textout(cout);
		}
		else if(str == "kind")
		{
			int x;
			cin >> x;
			auto res = stu.find_kind(x);
			for(auto i : res)
				i.textout(cout);
		}
		else
		{
			cout << "wrong" << endl;
			return true;
		}
		return false;
	}
	if(str == "add")
	{
		cout << "kind of acti: ";
		cin >> str;

		cout << "input acti: " << endl;
		Activity acti;
		acti.read(cin);

		if(str == "test")
		{
			// if(!admin)
				// return true;
			cout << "input class: ";
			string clas;
			cin >> clas;
			string res = add_acti(acti,clas);
			if(res!="addmin")
			{
				cout << "sudent" << res << "error" << endl;
				return true;
			}
		}
		else if(str == "acti")
			stu.insert_acti(acti);
		else
		{
			cout << "wrong" << endl;
			return true;
		}
		cout << "added" << endl;
		return false;
	}
	if(str == "set")
	{
		cout << "set alarm: ";
		return false;
	}
	if(str == "change")
	{
		cout << "kind of acti: ";
		cin >> str;

		cout << "input acti: " << endl;
		Activity acti;
		acti.read(cin);

		if(str == "test")
		{
			// if(!admin)
				// return true;
			cout << "input class: ";
			string clas;
			cin >> clas;
			string res = change_acti(acti,clas);
			if(res!="addmin")
			{
				cout << "sudent" << res << "error" << endl;
				return true;
			}
		}
		else if(str == "acti")
			stu.change_acti(acti);
		else
		{
			cout << "wrong" << endl;
			return true;
		}
		cout << "changed" << endl;
		return false;
	}
	if(str == "cancel")
	{
		cout << "kind of acti: ";
		cin >> str;

		cout << "input acti: " << endl;
		Activity acti;
		acti.read(cin);
	}
	return true;
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
				if(kbhit()) // 检测键盘输入
				{
					bool op = true;
					while(op)
					{
						cout << "check!" << endl;
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