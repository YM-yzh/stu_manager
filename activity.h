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
	int kind; // 5闹钟，4考试，3课程，2活动，1临时事务
	string name; // 活动名称

	Tome tome; // 活动时间
	int last; // 持续时长

	bool form; // 0线下，1线上
	string loca; // 线下地址或线上网址
	string room; // 线下教室房间号

	int freq; // 0单次，1每日，2每周

	void read(istream& ss);
	string textshow();
	void textout(ostream& xout);
};

bool cmp(Tome a, Tome b);
bool operator <= (Tome a, Tome b);
Tome operator + (Tome a, int b);

bool operator < (Activity a, Activity b);
bool operator <= (Activity a, Activity b);

const string week[8] = {"", "一", "二", "三", "四", "五", "六", "日"};
