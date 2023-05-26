#include "global.h"
#include "activity.h"

typedef vector<Activity> vA;
typedef vector<Activity>::iterator vAiter;

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

	int less_num;
	int acti_num;
	vA acti;
	// maps acti_dict;

public:
	void init(string user, string name, string id, string clas, string pass, string domi);
	bool check(string str);                                         // 检查密码

	void init_activity(ifstream& less, ifstream& acti);
	void save_activity(ostream& less, ostream& acti);
	void nless(int num);
	void nacti(int num);
	void merge();

	vAiter end();
	vAiter find_acti(Activity acti);                                  // 二分查找课程
	vAiter find_acti(string name);
	vAiter find_acti(Tome tome);
	vA find_acti(int kind);

	bool insert_acti(Activity acti);                                  // 二分查找课程
	bool change_acti(Activity acti);                                // 修改活动信息
	bool cancel_acti(string name);                                  // 取消活动

	bool add_alarm(string name, Tome tome, int freq);               // 闹钟

	vAiter getless();                                               // 获取活动数组开头
	void nextday(int day);
	void move(string& loca);
	void rest();

	string get_name();
	string get_class();
	int get_Location();

	void textout(ostream& xout);
	string textshow();
	void save(ostream& xout);
};

extern Student stu;

extern int num_stu;
extern Student stus[NUM];
extern maps stus_dict;

bool opins(vAiter tar, Activity acti);
void actiout(vA x);
void stuinit();
void stusave();

string add_acti(Activity acti, string clas);
string change_acti(Activity acti, string clas);
string cancel_acti(string name, string clas);
