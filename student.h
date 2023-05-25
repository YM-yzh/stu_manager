#include "global.h"
#include "activity.h"

typedef vector<Activity>::iterator vAiter;

extern ifstream info_stu;
extern string file_mkd;

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

extern int num_stu;
extern Student stus[NUM];
extern map<string, int, greater<string>> stus_dict;

bool opins(vAiter tar, Activity acti);
void actiout(vector<Activity> x);
void stuinit();
