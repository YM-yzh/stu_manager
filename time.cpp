#include "student.h"
#include <time.h>
#include <windows.h>

const int interval = 1;

void timestart()
{

	// nowtime
	// nextday::today activity
	// next time
	// now action
	// path
}

int main()
{
	cout << "正在载入地图信息..."  << endl;
	mapinit();
	cout << "正在载入学生信息..." << endl;
	stuinit();
	cout << "开始模拟" << endl;
	Sleep(1000*interval*4);
	system("cls");
	cout << "---- 学生日程管理系统 v1.0 ----"  << endl;
	// timestart();
	return 0;
}
