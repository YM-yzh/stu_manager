#include "student.h"
#include <time.h>
#include <conio.h>
#include <windows.h>

// #define ADMIN "da"
// #define PASS "488283"

// bool admin = false;

double interval = 2.0;

Student *stu;

void refresh(int tim)
{
	Sleep(1000 / interval * tim);
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

void putime(Tome tt)
{
	cout << " 星期" << week[tt.day] << ' ';
	cout << setw(2) << setfill(' ') << tt.hour << "点";
}

bool action(string &str)
{
	cout << str << endl;
	if (str == "save")
		subsave();
	if (str == "set")
	{
		cout << "set speed: ";
		cin >> interval;
		return false;
	}
	if (str == "error")
	{
		cout << "error" << endl;
		return false;
	}
	if (str == "show")
	{
		// cout << stu->get_num() << endl;
		stu->save_activity(cout, cout);
		return false;
	}
	if (str == "find")
	{
		cout << "kind of find: ";
		cin >> str;
		if (str == "name")
		{
			cin >> str;
			auto res = stu->find_acti(str);
			res->textout(cout);
		}
		else if (str == "tome")
		{
			Tome tome;
			cin >> tome.day >> tome.hour;
			auto res = stu->find_acti(tome);
			res->textout(cout);
		}
		else if (str == "kind")
		{
			int x;
			cin >> x;
			auto res = stu->find_acti(x);
			for (auto i : res)
				i.textout(cout);
		}
		else
		{
			cout << "wrong" << endl;
			return true;
		}
		return false;
	}
	if (str == "add")
	{
		cout << "kind of acti: ";
		cin >> str;

		cout << "input acti: " << endl;
		Activity acti;
		acti.read(cin);

		if (str == "test")
		{
			// if(!admin)
			// {
			// 	cout << "permission denied" << endl;
			// 	return true;
			// }
			cout << "input class: ";
			string clas;
			cin >> clas;
			string res = add_acti(acti, clas);
			if (res != "addmin")
			{
				cout << "sudent" << res << "error" << endl;
				return true;
			}
		}
		else if (str == "acti")
		{
			auto res = stu->insert_acti(acti);
			if (res.size() == 0 || res.begin()->first.day > 0)
			{
				cout << "failed" << endl;
				cout << "possible time:" << endl;
				for (auto i : res)
				{
					putime(i.first);
					cout << " ~ ";
					putime(i.second);
					cout << endl;
				}
				return true;
			}
		}
		else
		{
			cout << "wrong" << endl;
			return true;
		}
		cout << "added" << endl;
		return false;
	}
	if (str == "alarm")
	{
		cout << "input acti: " << endl;
		Activity acti;
		acti.read(cin);

		cout << "set alarm: ";
		Tome alarm;
		int freq;
		cin >> alarm.day >> alarm.hour;

		bool op = stu->add_alarm(acti, alarm);
		if (!op)
			cout << "failed" << endl;
		return false;
	}
	if (str == "change")
	{
		cout << "kind of acti: ";
		cin >> str;

		cout << "input acti: " << endl;
		Activity acti;
		acti.read(cin);

		if (str == "test")
		{
			// if(!admin)
			// {
			// 	cout << "permission denied" << endl;
			// 	return true;
			// }
			cout << "input class: ";
			string clas;
			cin >> clas;
			string res = change_acti(acti, clas);
			if (res != "addmin")
			{
				cout << "sudent" << res << "error" << endl;
				return true;
			}
		}
		else if (str == "acti")
			stu->change_acti(acti);
		else
		{
			cout << "wrong" << endl;
			return true;
		}
		cout << "changed" << endl;
		return false;
	}
	if (str == "cancel")
	{
		cout << "kind of acti: ";
		cin >> str;

		cout << "input acti name: ";
		string ssr;
		cin >> ssr;

		if (str == "test")
		{
			// if(!admin)
			// {
			// 	cout << "permission denied" << endl;
			// 	return true;
			// }
			cout << "input class: ";
			string clas;
			cin >> clas;
			string res = cancel_acti(ssr, clas);
			if (res != "addmin")
			{
				cout << "sudent" << res << "error" << endl;
				return true;
			}
		}
		else if (str == "acti")
		{
			bool op = stu->cancel_acti(ssr);
			if (!op)
			{
				cout << "wrong" << endl;
				return true;
			}
		}
		else
		{
			cout << "wrong" << endl;
			return true;
		}
		cout << "canceled" << endl;
		return false;
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
	if (op == stus_dict.end())
		return -1;

	id = stus_dict[username];
	stu = &stus[id];

	bool status = true;

	for (int wrong = 0; status; wrong++)
	{
		if (wrong > 0)
			cout << "密码错误！" << endl;
		cout << "请输入密码: ";
		cin >> password;
		if (stu->check(password))
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

	for (int status = login(); status == -1; status = login())
		;
	cout << "登陆成功！" << endl;
	debugout << stu->get_user() << " login" << endl;
	refresh(2);
}

// nowtime
// nextday::today activity
// next time
// now action
// path

bool operator < (Temp::BB a, Temp::BB b)
{
	int aid = buid_dict[a.loca];
	int bid = buid_dict[b.loca];
	int mid = stu->get_Location();
	return dis[mid][aid] < dis[mid][bid];
}

bool action(Activity acti)
{
	if (acti.kind > 3 || acti.kind == 2)
	{
		acti.textout(cout);
		if (acti.form == 0)
			stu->move(acti.loca);
	}
	else if (acti.kind == 3)
	{
		acti.alarmout(cout);
		if (acti.form == 0)
			stu->move(acti.loca);
	}
	else if (acti.kind == 1)
	{
		// sort (acti.tt.temp_acti + 1, acti.tt.temp_acti + acti.tt.num);
		multi_go(stu->get_Location(), acti.tt);
	}
	switch (acti.freq)
	{
	case 1:
		acti.tome.nextday();
		stu->insert_acti(acti);
	case 0:
		return true;
	}
	return false;
}

void timestart()
{
	while (true)
	{
		Month mm = {2, 19};
		Tome now = {7, eNd};
		vAiter acti = stu->begin();
		for (int i = 1; i <= 7; i++)
		{
			// loop(acti, now);
			cout << "今天日程已结束!" << endl;
			stu->rest();
			cout << endl
				 << "明天日程: ";
			stu->nextday(now.day, acti); // 输出第二天日程

			for (int j=0; j<23; j++)
			{
				if (kbhit()) // 检测键盘输入
				{
					cout << "check input!" << endl;
					acti->textout(cout);
					bool op = true;
					while (op)
					{
						cout << "check input!" << endl;
						string order;
						cin >> order;
						op = action(order);
					}
				}

				mm.putime(cout);
				now.putime(cout);
				Sleep(1000 / interval);
				int step = now.nextime();
				if (step)
					mm.next();
				// if (step > 1)
					// acti = stu->begin();

				if (now.hour == acti->tome.hour)
				{
					if (action(*acti))
						acti = stu->erase_acti(acti);
					else acti++;

					// action(*acti);
					// // acti->textout(cout);
					// acti++;
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
