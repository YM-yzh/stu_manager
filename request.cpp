#include "student.cpp"

void preload()
{
	cout << "正在载入地图信息..." << endl;
	mapinit();
	cout << "正在载入学生信息..." << endl;
	stuinit();
}

int main()
{
	preload();
	stutest();
	return 0;
}
