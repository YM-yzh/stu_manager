#include "student.h"

int num_stu = 0;
Student stus[NUM] = {};
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

void Student::init_lesson(ifstream& ss)
{
	ss >> this->acti_num;
	Activity x;
	for(int i=1;i<=acti_num;i++)
	{
		x.read(ss);
		this->acti.push_back(x);
		this->acti_dict.emplace(x.name, i-1);
	}
	sort(this->acti.begin(), this->acti.end());
	// actiout(this->acti);
}

vAiter Student::find_acti(string name)
{
	for(vAiter i = this->acti.begin();i!=this->acti.end();i++)
		if(i->name == name)
			return i;
	return this->acti.end();
}

bool opins(vAiter tar, Activity acti)
{
	Activity l = *tar;
	Activity r = *(tar+1);
	return (l.tome+l.last) <= (acti.tome) && (acti.tome+acti.last) <= r.tome;
}

bool Student::find_acti(Activity acti)
{
	vAiter targt;
	// vAiter targt = lower_bound(this->acti.begin(), this->acti.end(), acti);
	int left = 0;
	int right = this->acti_num - 1;
	while(left <= right)
	{
		int mid = (left + right) / 2;
		vAiter now = this->acti.begin()	+ mid;
		if ((*now) <= acti)
			left = mid+1;
		else
			right = mid-1;
	}
	targt = this->acti.begin() + left - 1;
	if(!opins(targt, acti))
		return false;
	this->acti.insert(targt+1, acti);
	this->acti_num++;
	return true;
}

bool Student::change_acti(Activity acti)
{
	bool flag = this->cancel_acti(acti.name);
	if (!flag)
		return false;
	flag = this->find_acti(acti); // 为了维护有序序列，先取消原有日程，再添加
	return flag;
}

bool Student::cancel_acti(string name)
{
	auto targt = this->find_acti(name);
	if(targt==this->acti.end())
		return false;
	this->acti.erase(targt);
	this->acti_num--;
	return true;
}

void Student::textout(ostream& xout)
{
	xout << this->user << endl;
	xout << this->name << ' ' << this->id << ' ' << this->pass << ' ' << this->domi << endl;
	xout << this->acti_num << endl;
	for(auto i : this->acti)
		i.textout(xout);
}

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

		stus[i].textout(debugout);
	}
}
