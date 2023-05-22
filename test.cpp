#include "student.h"

const double interval = 0.5;

Student stu;

int login()
{
	int id = 1;
	string username, password;
	bool status = true;

	cout << "请输入用户名/学号: ";
	cin >> username;

	id = stus_dict[username];
	stu = stus[id];

	while (status)
	{
		cout << "请输入密码: ";
		cin >> password;
		if (stu.check(password))
			status = false;
	}
	return id;
}

// nowtime
// nextday::today activity
// next time
// now action
// path

void Sleep(int tim)
{
	int a = 0;
	for(int i=1;i<=1e8*tim;i++)
		a = a+1;
}

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
 			cout << endl << "明天日程: ";
			stu.nextday(now.day); // 输出第二天日程

			for(int i=1;i<=24;i++)
			{
				now.putime(cout);
				Sleep(interval*2);
				now.nextime();
				if(now.hour == atci->tome.hour)
				{
					atci->textout(cout);
					atci++;
				}
			}
		}
	}
}

void refresh(int tim)
{
	Sleep(interval * tim);
	// system("clear");
	cout << "---- 学生日程管理系统 v1.0 ----" << endl;
}

void preload()
{
	cout << "正在载入地图信息..." << endl;
	mapinit();
	cout << "正在载入学生信息..." << endl;
	stuinit();
	cout << "开始模拟" << endl;
	refresh(2);

	int status = login();
	if (!status)
	{
		// crash();
		exit(0);
	}
	cout << "登陆成功！" << endl;
	refresh(2);
}

int main()
{
	preload();
	timestart();
	return 0;
}
