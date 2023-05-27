#include "activity.h"

bool operator<(Tome a, Tome b)
{
	return (a.day == b.day) ? a.hour < b.hour : a.day < b.day;
}

bool operator==(Tome a, Tome b)
{
	return (a.day == b.day) && (a.hour == b.hour);
}

bool operator<=(Tome a, Tome b)
{
	return (a.day == b.day) ? a.hour <= b.hour : a.day < b.day;
}

Tome operator+(Tome a, int b)
{
	return (Tome){a.day, a.hour + b};
}

bool operator<(Activity a, Activity b)
{
	return a.tome < b.tome;
}

bool operator<=(Activity a, Activity b)
{
	return a.tome <= b.tome;
}

void Month::next()
{
	this->day++;
	if (this->day > mon[this->month])
	{
		this->day = 1;
		this->month++;
	}
}

int Tome::nextime()
{
	int status = 0;
	this->hour++;
	if (this->hour == 24)
	{
		this->hour = 0;
		this->day++;
		status++;
	}
	if (this->day == 8)
	{
		this->day = 1;
		status++;
	}
	switch (status)
	{
	case 2:
		cout << "新的一周!" << endl;
	case 1:
		cout << "新的一天! "
			 << "今天星期" << week[this->day] << endl;
	default:
		break;
	}
	return status;
}

void Tome::nextday()
{
	this->day++;
	if (this->day == 8)
		this->day = 1;
}

void Tome::outime(ostream &xout)
{
	xout << "现在是星期" << week[this->day] << ' ' << this->hour << "点" << endl;
}

void Month::putime(ostream &xout)
{
	xout << "现在是" << setw(2) << setfill(' ') << this->month << "月";
	xout << setw(2) << setfill(' ') << this->day << "日";
}

void Tome::putime(ostream &xout)
{
	xout << " 星期" << week[this->day] << ' ';
	xout << setw(2) << setfill(' ') << this->hour << "点" << endl;
}

void Activity::read(istream &ss)
{
	ss >> this->name >> this->kind;
	ss >> this->tome.day >> this->tome.hour >> this->last;
	ss >> this->form >> this->loca;
	// if(!this->form)
	ss >> this->room; // 线下课程输入房间号
	ss >> this->freq;
}

void Activity::write(ostream &ss)
{
	// ss << this->name << ' ' << this->kind << ' ';
	ss << this->name << ' ' << ((this->kind == 1)?2:this->kind) << ' ';
	ss << this->tome.day << ' ' << this->tome.hour << ' ' << this->last << ' ';
	ss << this->form << ' ' << this->loca << ' ';
	// if(!this->form)
	ss << this->room << ' ';
	ss << this->freq << endl;
}

void Activity::textout(ostream &xout)
{
	xout << "星期" << week[this->tome.day] << ' ';
	xout << setw(2) << setfill(' ') << this->tome.hour << "点 ~ ";
	xout << setw(2) << setfill(' ') << this->tome.hour + this->last << "点 ";
	xout << this->loca << ' ' << this->room << ' ' << this->name << endl;
}

string Activity::textshow()
{
	string str = "";
	str += "星期" + week[this->tome.day] + ' ';
	str += (char)('0' + this->tome.hour) + "点 ~ ";
	str += (char)('0' + this->tome.hour + this->last) + "点 ";
	str += this->loca + ' ' + this->room + ' ' + this->name;
	return str;
}
