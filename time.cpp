#include "student.h"
#include <time.h>
#include <windows.h>

const int interval = 1;

int login()
{
	int id;
	string username;
	bool status = 1;

	cout << "请输入用户名/学号: ";
	cin >> username;
	while(status)
	{
		cout << "请输入密码: ";
		if(true)
			status = false;
	}
	return id;
}

void timestart(int id)
{

	// nowtime
	// nextday::today activity
	// next time
	// now action
	// path
}

void refresh(int tim)
{
	Sleep(1000 * interval * tim);
	system("cls");
	cout << "---- 学生日程管理系统 v1.0 ----"  << endl;
}

int main()
{
	cout << "正在载入地图信息..."  << endl;
	mapinit();
	cout << "正在载入学生信息..." << endl;
	stuinit();
	cout << "开始模拟" << endl;
	refresh(2);

	int id=login();
	if(id)
		cout << "登陆成功！"  << endl;
	else
	{
		// crash();
		return 1;
	}
	refresh(2);
	timestart(id);
	return 0;
}
