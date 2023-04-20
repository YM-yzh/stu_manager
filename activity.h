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

class Activity // 学生活动信息
{
private:
	bool kind; // 0表示课程，1表示活动
	string name;
	Tome tome;
	int last; // 持续时长
	int frequency;
	bool form; // 0表示线下，1表示线上
	Position loca; // 线下地址或线上网址

public:
	void init_lesson(string nam, Tome tome, int last, Position loca, bool op);
	void init_activity(string nam, Tome tome, Position loc, bool op);
	void change_activity(string nam, Tome begin, Tome end, Position loc, bool op);
	void cancel_activity(string nam);
};

bool operator < (Activity a, Activity b)
{
	return a.tome < b.tome;
}

void Activity::init_lesson(string nam, Tome tome, int last, Position loca, bool op)
{

}
