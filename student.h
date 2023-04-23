#include "activity.h"

typedef vector<Activity>::iterator vAiter;

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

	int acti_num;
	vector<Activity> acti;
	map<string, int, greater<string>> acti_dict;

public:
	void init(string user, string name, int id, string pass, string domi);
	void init_lesson(ifstream& ss);
	void change_activity(string nam, Tome begin, Tome end, Position loc, bool op);
	void cancel_activity(string nam);

	vAiter getless();
	void nextday(int day);

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

vAiter Student::getless()
{
	return this->acti.begin();
}

void Student::nextday(int day)
{
	day = day%7 + 1;
	cout << "星期" << week[day] << endl;
	for(auto i : this->acti)
	{
		if(i.tome.day > day)
			break;
		cout << setw(2) << setfill(' ') << i.tome.hour << "点 ~ ";
		cout << setw(2) << setfill(' ') << i.tome.hour + i.last << "点 ";
		cout << i.loca << ' ' << i.name << endl;
	}
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
	ss >> this->acti_num;
	Activity x;
	for(int i=1;i<=acti_num;i++)
	{
		ss >> x.name >> x.tome.day >> x.tome.hour >> x.last >> x.form >> x.loca >> x.frequency;
		this->acti.push_back(x);
		this->acti_dict.emplace(x.name, i-1);
	}
	sort(this->acti.begin(), this->acti.end());
	// actiout(this->acti);
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
