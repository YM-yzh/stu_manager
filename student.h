#include "activity.h"

int num_stu;
map<int, int> stu;

ifstream info_stu(file_path + "student/student_info.in");
string file_mkd = file_path + "student/stu_";

class Student // 学生基本信息
{
private:
	int id;
	string name;
	string pass;
	string domi;
	Position now;

	int less_num;
	vector<Activity> less;
	int acti_num;
	vector<Activity> less;

public:
	void set_id(int newid);
	void set_name(string str);
	int get_id();
	void set_domitory(Position loca);
	Position get_Location();
};

vector<Student> stu;

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

void stuinit()
{
	info_stu >> num_stu;

	string ss;
	for (int i = 1; i <= num_stu; i++)
	{
		info_stu >> ss;
		ifstream info_ss(file_mkd + ss + "/lesson.in");
	}
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
