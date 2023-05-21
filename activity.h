#include "school.h"

struct Tome
{
	int day; // 表示星期
	int hour; // 以小时为单位进行活动

	void nextime();
	void outime(ostream& xout);
	void putime(ostream& xout);
};

const string week[8] = {"", "一", "二", "三", "四", "五", "六", "日"};

void Tome::nextime()
{
	int status = 0;
	this->hour++;
	if(this->hour == 24)
	{
		this->hour = 0;
		this->day++;
		status++;
	}
	if(this->day == 8)
	{
		this->day = 1;
		status++;
	}
	switch(status)
	{
		case 2: cout << "新的一周!" << endl;
		case 1: cout << "新的一天! " << "今天星期" << week[this->day] << endl;
		default: break;
	}
}

void Tome::outime(ostream& xout)
{
	xout << "现在是星期" << week[this->day] << ' ' << this->hour << "点" << endl;
}

void Tome::putime(ostream& xout)
{
	xout << "现在是" << setw(2) << setfill(' ') << this->hour << "点" << endl;
}

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
	string room; // 线下教室房间号

	bool frequency; // 1表示单次，0表示每周

	void textout(ostream& xout);
};

bool operator < (Activity a, Activity b)
{
	return a.tome < b.tome;
}

void Activity::textout(ostream& xout)
{
	xout << setw(2) << setfill(' ') << this->tome.hour << "点 ~ ";
	xout << setw(2) << setfill(' ') << this->tome.hour + this->last << "点 ";
	xout << this->loca << ' ' << this->name << endl;
}
