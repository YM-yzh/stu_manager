#include "student.h"

void preload()
{
	cout << "正在载入地图信息..." << endl;
	mapinit();
	cout << "正在载入学生信息..." << endl;
	stuinit();
}

Student stu;

void login()
{
	string username = "yzh";
	int id = stus_dict[username];
	stu = stus[id];

}

ifstream info_reqs(file_path + "requests.in");
ofstream testout(file_path + "requests.out");

void stutest()
{
	int num_reqs;
	Activity x;

	info_reqs >> num_reqs;

	for (int i = 1; i <= num_reqs; i++)
	{
		x.read(info_reqs);
		bool flag = stu.find_acti(x);
		testout << i << flag << endl;
	}
	stu.textout(testout);

	info_reqs >> num_reqs;

	for (int i = 1; i <= num_reqs; i++)
	{
		string str;
		info_reqs >> str;
		bool flag = stu.cancel_acti(str);
		testout << i << flag << endl;
	}
	stu.textout(testout);

	info_reqs >> num_reqs;

	for (int i = 1; i <= num_reqs; i++)
	{
		x.read(info_reqs);
		bool flag = stu.change_acti(x);
		testout << i << flag << endl;
	}
	stu.textout(testout);
}

int main()
{
	preload();
	login();
	stutest();
	return 0;
}
