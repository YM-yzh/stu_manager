#include "school.h"

struct Tome
{
	int day; // 表示星期
	int hour; // 以小时为单位进行活动
};

bool operator < (Tome a, Tome b)
{
	return (a.day == b.day) ? a.hour < b.hour : a.day < b.day;
}

struct Activity // 学生活动信息
{
	bool kind; // 0表示课程，1表示活动
	string name;

	Tome tome;
	int last; // 持续时长

	bool form; // 0表示线下，1表示线上
	string loca; // 线下地址或线上网址

	int frequency;
};

bool operator < (Activity a, Activity b)
{
	return a.tome < b.tome;
}
