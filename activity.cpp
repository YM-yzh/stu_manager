#include "school.h"

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

void Activity::read(istream& ss)
{
	ss >> this->name >> this->tome.day >> this->tome.hour >> this->last >> this->form >> this->loca;
	if(!this->form)
		ss >> this->room; // 线下课程输入房间号
	ss >> this->frequency;
}

void Activity::textout(ostream& xout)
{
	xout << setw(2) << setfill(' ') << this->tome.hour << "点 ~ ";
	xout << setw(2) << setfill(' ') << this->tome.hour + this->last << "点 ";
	xout << this->loca << ' ' << this->name << endl;
}
