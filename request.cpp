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
	int num_reqs;
	string a, b;

	info_reqs >> num_reqs;

	for (int i = 1; i <= num_reqs; i++)
	{
		info_reqs >> a >> b;
		int aid = buid_dict[a];
		int bid = buid_dict[b];

		debugout << i << endl;
		Go(aid, bid);
		debugout << endl;
	}
}

int main()
{
	preload();
	stutest();
	return 0;
}
