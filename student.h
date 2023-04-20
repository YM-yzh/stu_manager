#include "activity.h"

int num_stu;
map<int, int> stu;

ifstream info_stu("./testin/student/student_info.in");

class Student // 学生基本信息
{
private:
	int id;
	string name;
	string pass;
	string domi;
	Position now;

	int less_num;


public:
	void set_id(int newid);
	void set_name(string str);
	int get_id();
	void set_domitory(Position loca);
	Position get_Location();
};

void Student::set_id(int newid)
{
	this->id = newid;
}

int Student::get_id()
{
	return this->id;
}

void Student::set_domitory(Position loca)
{
	this->now = loca;
}

Position Student::get_Location()
{
	return this->now;
}

void stutest()
{
	int num_reqs;
	string a, b;

	info_schl >> num_reqs;

	for (int i = 1; i <= num_reqs; i++)
	{
		info_stu >> a >> b;
		int aid = dict[a];
		int bid = dict[b];

		testout << i << endl;
		Go(aid, bid);
		testout << endl;
	}
}

void stuinit()
{
	int num_reqs;
	string a, b;

	info_schl >> num_reqs;

	for (int i = 1; i <= num_reqs; i++)
	{
		info_stu >> a >> b;
		int aid = dict[a];
		int bid = dict[b];

		testout << i << endl;
		Go(aid, bid);
		testout << endl;
	}
}
