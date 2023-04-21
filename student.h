#include "activity.h"

ifstream info_stu(file_path + "student/student_info.in");
string file_mkd = file_path + "student/stu_";

class Student // 学生基本信息
{
private:
	int id;
	string user;
	string name;
	string pass;
	string domi;
	Position now;

	int less_num;
	vector<Activity> less;

	int acti_num;
	vector<Activity> acti;
	map<string, int, greater<string>> acti_dict;

public:
	void init(string user, string name, int id, string pass, string domi);
	void init_lesson(ifstream& ss);
	void change_activity(string nam, Tome begin, Tome end, Position loc, bool op);
	void cancel_activity(string nam);

	int get_id();
	Position get_Location();
};

int num_stu;
Student stus[NUM];
map<int, int> stu_dict;

void Student::init(string user, string name, int id, string pass, string domi)
{
	this->user = user;
	this->name = name;
	this->id = id;
	this->pass = pass;
	this->domi = domi;
}

int Student::get_id()
{
	return this->id;
}

Position Student::get_Location()
{
	return this->now;
}

void actiout(vector<Activity> x)
{
	for(auto i : x)
		testout << i.name << endl;
}

void Student::init_lesson(ifstream& ss)
{
	ss >> this->less_num;
	Activity x;
	for(int i=1;i<=less_num;i++)
	{
		ss >> x.name >> x.tome.day >> x.tome.hour >> x.last >> x.form >> x.loca >> x.frequency;
		this->less.push_back(x);
	}
	sort(this->less.begin(), this->less.end());
	// actiout(this->less);
}

void stuinit()
{
	info_stu >> num_stu;

	string name, pass, domi;
	int id;

	string ss;
	ifstream info_ss;
	for (int i = 1; i <= num_stu; i++)
	{
		info_stu >> ss;
		info_ss.open(file_mkd + ss + "/_info.in");

		info_ss >> name >> id >> pass >> domi;
		stus[i].init(ss,name, id, pass, domi);

		info_ss.close();
		info_ss.open(file_mkd + ss + "/lesson.in");
		stus[i].init_lesson(info_ss);
		info_ss.close();
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
		int aid = buid_dict[a];
		int bid = buid_dict[b];

		testout << i << endl;
		Go(aid, bid);
		testout << endl;
	}
}
