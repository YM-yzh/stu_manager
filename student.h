#include "acti.h"

typedef vector<Activity>::iterator vAiter;

ifstream info_stu(file_path + "student/student_info.in");
string file_mkd = file_path + "student/stu_";

class Student // 学生
{
private:
	string user;
	string pass;

	string id;
	string clas;
	string name;

	string domi;
	int now;

	int acti_num;
	vector<Activity> acti;
	map<string, int, greater<string>> acti_dict;

public:
	void init(string user, string name, string id, string clas, string pass, string domi);
	bool check(string str);                                         // 检查密码

	void init_lesson(ifstream& ss);
	int find_acti(string name);                                     // 二分查找课程
	void change_acti(Activity acti);                                // 修改活动信息
	void cancel_acti(string name);                                  // 取消活动

	void add_alarm(string name, Tome tome, int freq);               // 闹钟
	void add_test(Activity test);                                   //管理员添加考试

	vAiter getless();                                               // 获取活动数组开头
	void nextday(int day);
	void move(string& loca);
	void rest();

	string get_class();
	int get_Location();

	void textout(ostream& xout);
};

int num_stu;
Student stus[NUM];
map<string, int, greater<string>> stus_dict;

void Student::init(string user, string name, string id, string clas, string pass, string domi)
{
	this->user = user;
	this->pass = pass;

	this->name = name;
	this->id = id;
	this->clas = clas;
	this->domi = domi;
	this->now = buid_dict[domi];
}

bool Student::check(string str)
{
	return str == this->pass;
}

vAiter Student::getless()
{
	return this->acti.begin();
}

string Student::get_class()
{
	return this->clas;
}

void Student::nextday(int day)
{
	day = day%7 + 1;
	cout << "星期" << week[day] << endl;
	for(auto i : this->acti)
	{
		if(i.tome.day < day)
			continue;
		if(i.tome.day > day)
			break;
		cout << setw(2) << setfill(' ') << i.tome.hour << "点 ~ ";
		cout << setw(2) << setfill(' ') << i.tome.hour + i.last << "点 ";
		cout << i.loca << ' ' << i.name << endl;
	}
}

void Student::move(string& loca)
{
	int aid = this->now;
	int bid = buid_dict[loca];
	Go(aid, bid);
	this->now = bid;
}

void Student::rest()
{
	this->now = buid_dict[this->domi];
}

int Student::get_Location()
{
	return this->now;
}

void actiout(vector<Activity> x)
{
	for(auto i : x)
		debugout << i.name << endl;
}

void Student::init_lesson(ifstream& ss)
{
	ss >> this->acti_num;
	Activity x;
	for(int i=1;i<=acti_num;i++)
	{
		ss >> x.name >> x.tome.day >> x.tome.hour >> x.last >> x.form >> x.loca;
		if(!x.form)
			ss >> x.room; // 线下课程输入房间号
		ss >> x.frequency;
		this->acti.push_back(x);
		this->acti_dict.emplace(x.name, i-1);
	}
	sort(this->acti.begin(), this->acti.end());
	// actiout(this->acti);
}

int Student::find_acti(string name)
{
	return -1;
}

void Student::change_acti(Activity acti)
{
	int seq = this->find(acti.name);
	vAiter targt = this->acti.begin() + seq;
	*targt = acti;
}

void Student::cancel_acti(string name)
{

}

void Student::textout(ostream& xout)
{
	xout << this->user << endl;
	xout << this->name << ' ' << this->id << ' ' << this->pass << ' ' << this->domi << endl;
	xout << this->acti_num << endl;
	for(auto i : this->acti)
		i.textout(debugout);
}

void stuinit()
{
	info_stu >> num_stu;

	string name, pass, domi;
	string id, clas;

	string ss;
	ifstream info_ss;
	for (int i = 1; i <= num_stu; i++)
	{
		info_stu >> ss;
		info_ss.open(file_mkd + ss + "/_info.in");

		info_ss >> name >> id >> clas >> pass >> domi;
		stus[i].init(ss,name, id, clas, pass, domi);
		// stus_dict.emplace(id, i);
		stus_dict.emplace(ss, i);

		info_ss.close();
		info_ss.open(file_mkd + ss + "/lesson.in");
		stus[i].init_lesson(info_ss);
		info_ss.close();

		// stus[i].textout(debugout);
	}
}

ifstream info_reqs(file_path + "requests.in");

void stutest()
{
	int num_reqs;
	string a, b;

	info_reqs >> num_reqs;

	for (int i = 1; i <= num_reqs; i++)
	{
		info_reqs >> a >> b;
		int aid = buid_dict[a];
		int bid = buid_dict[b];

		debugout << i << endl;
		Go(aid, bid);
		debugout << endl;
	}
}
