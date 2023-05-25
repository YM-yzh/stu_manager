#include "global.h"
#include "school.h"

struct Tome
{
	int day; // 表示星期
	int hour; // 以小时为单位进行活动

	void nextime();
	void outime(ostream& xout);
	void putime(ostream& xout);
};

struct Activity // 学生活动信息
{
	int kind; // 2表示考试，1表示课程，0表示活动/临时事务
	string name; // 活动名称

	Tome tome; // 活动时间
	int last; // 持续时长

	bool form; // 0表示线下，1表示线上
	string loca; // 线下地址或线上网址
	string room; // 线下教室房间号

	bool frequency; // 1表示单次，0表示每周

	void read(istream& ss);
	void textout(ostream& xout);
};

bool cmp(Tome a, Tome b);
bool operator <= (Tome a, Tome b);
Tome operator + (Tome a, int b);

bool operator < (Activity a, Activity b);
bool operator <= (Activity a, Activity b);

const string week[8] = {"", "一", "二", "三", "四", "五", "六", "日"};
