#include "activity.h"

typedef vector<Activity>::iterator vAiter;

ifstream info_stu(file_path + "student/student_info.in");
string file_mkd = file_path + "student/stu_";

int num_stu;
Student stus[NUM];
map<string, int, greater<string>> stus_dict;

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
	vAiter find_acti(string name);
	bool find_acti(Activity acti);                                  // 二分查找课程
	bool change_acti(Activity acti);                                // 修改活动信息
	bool cancel_acti(string name);                                  // 取消活动

	void add_alarm(string name, Tome tome, int freq);               // 闹钟
	void add_test(Activity test);                                   // 管理员添加考试

	vAiter getless();                                               // 获取活动数组开头
	void nextday(int day);
	void move(string& loca);
	void rest();

	string get_class();
	int get_Location();

	void textout(ostream& xout);
};

void actiout(vector<Activity> x)
{
	for(auto i : x)
		debugout << i.name << endl;
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
