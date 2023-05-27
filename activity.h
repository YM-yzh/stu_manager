#pragma once
#include "global.h"
#include "school.h"

struct Month
{
	int month;
	int day;

	void next();
	void putime(ostream &xout);
};

struct Tome
{
	int day;  // 表示星期
	int hour; // 以小时为单位进行活动

	int nextime();
	void nextday();
	void outime(ostream &xout);
	void putime(ostream &xout);
};

struct Temp
{
	Tome tome;
	int temp_num;
	struct
	{
		string name, loca;
	} temp_acti[5]; // 临时事务可以同时完成
};

struct Activity // 学生活动信息
{
	int kind;	 // 5考试，4课程，3闹钟，2活动，1临时事务
	string name; // 活动名称

	Tome tome; // 活动时间
	int last;  // 持续时长

	bool form;	 // 0线下，1线上
	string loca; // 线下地址或线上网址
	string room; // 线下教室房间号

	int freq; // 0单次，1每日，2每周

	Tome that;
	Temp tt;

	void read(istream &ss);
	void write(ostream &ss);
	string textshow();
	void textout(ostream &xout);
};

typedef vector<Activity> vA;
typedef vector<Activity>::iterator vAiter;

bool operator<(Tome a, Tome b);
bool operator==(Tome a, Tome b);
bool operator<=(Tome a, Tome b);
Tome operator+(Tome a, int b);

bool operator<(Activity a, Activity b);
bool operator<=(Activity a, Activity b);

const string week[8] = {"", "一", "二", "三", "四", "五", "六", "日"};

const int mon[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
