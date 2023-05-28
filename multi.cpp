#include "student.h"

void preload()
{
	cout << "正在载入地图信息..." << endl;
	mapinit();
	cout << "正在载入学生信息..." << endl;
	stuinit();
}

ifstream info_reqs(file_path + "requests.in");
ofstream testout(file_path + "requests.out");

void stutest()
{
	Temp tt;
	string now;

	info_reqs >> now;
	info_reqs >> tt.num;
	for(int i=1;i<=tt.num;i++)
	{
		info_reqs >> tt.temp_acti[i].name;
		info_reqs >> tt.temp_acti[i].loca;
	}
	multi_go(buid_dict[now], tt);
}

int main()
{
	preload();
	stutest();
	return 0;
}
