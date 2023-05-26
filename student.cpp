#include "student.h"

int num_stu = 0;
Student stus[NUM] = {};
maps stus_dict;

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

string Student::get_name()
{
	return this->name;
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

void Student::save_lesson(ostream& ss)
{
	ss << this->acti_num << endl;
	for(auto i : this->acti)
	{
		ss << i.name << ' ' << i.kind << ' ';
		ss << i.tome.day << ' ' << i.tome.hour << ' ' << i.last << ' ';
		ss << i.form << ' ' << i.loca << ' ';
		// if(!i.form)
			ss << i.room << ' '; // 线下课程输入房间号
		ss << i.freq << endl;
	}
}

vAiter Student::end()
{
	return this->acti.end();
}

vA Student::find_kind(int kind)
{
	vA res = {};
	for(auto i : this->acti)
		if(i.kind == kind)
			res.push_back(i);
	return res;
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

bool Student::insert_acti(Activity acti)
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
	flag = this->insert_acti(acti); // 为了维护有序序列，先取消原有日程，再添加
	return flag;
}

bool Student::cancel_acti(string name)
{
	auto targt = this->find_acti(name);
	if(targt==this->end())
		return false;
	this->acti.erase(targt);
	this->acti_num--;
	return true;
}

bool Student::add_alarm(string name, Tome tome, int freq)
{
	Activity alarm = {};
	alarm.kind = 3;
	alarm.name = name;
	alarm.tome = tome;
	alarm.last = 0;
	alarm.freq = freq;
	return this->insert_acti(alarm);
}

void Student::textout(ostream& xout)
{
	xout << this->user << endl;
	xout << this->name << ' ' << this->id << ' ' << this->pass << ' ' << this->domi << endl;
	xout << this->acti_num << endl;
	for(auto i : this->acti)
		i.textout(xout);
}

void Student::save(ostream& xout)
{
	xout << this->name << endl;
	xout << this->id << endl;
	xout << this->clas << endl;
	xout << this->pass << endl;
	xout << this->domi << endl;
}

void actiout(vector<Activity> x)
{
	for(auto i : x)
		debugout << i.name << endl;
}

void stuinit()
{
	ifstream info_stu(file_path + "student/student_info.in");
	info_stu >> num_stu;
	if(num_stu > NUM)
	{
		debugout << "student info error" << endl;
		cout << "学生信息错误！" << endl;
		system("pause");
		exit(0);
	}

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
		debugout << ss << " info read" << endl;
		info_ss.close();

		info_ss.open(file_mkd + ss + "/lesson.in");
		stus[i].init_lesson(info_ss);
		debugout << ss << " lesson read" << endl;
		info_ss.close();

		stus[i].textout(debugout);
	}
	info_stu.close();
}

void stusave()
{
	ifstream info_stu(file_path + "student/student_info.in");

	info_stu >> num_stu;

	string name, pass, domi;
	string id, clas;

	string ss;
	ofstream save_ss;
	for (int i = 1; i <= num_stu; i++)
	{
		info_stu >> ss;
		save_ss.open(save_mkd + ss + "/_info.in");

		Student stu = stus[i];
		stu.save(save_ss);
		debugout << ss << " info saved" << endl;
		save_ss.close();

		save_ss.open(save_mkd + ss + "/lesson.in");
		stus[i].save_lesson(save_ss);
		debugout << ss << " lesson saved" << endl;
		save_ss.close();
	}
	info_stu.close();
}

// #ifdef ADMIN

string add_acti(Activity acti, string clas)
{
	for(int i=1;i<=num_stu;i++)
	{
		if(stus[i].get_class() == clas)
		{
			bool op = stus[i].insert_acti(acti);
			if(!op)
				return stus[i].get_name();
		}
	}
	return "addmin";
}

string change_acti(Activity acti, string clas)
{
	for(int i=1;i<=num_stu;i++)
	{
		if(stus[i].get_class() == clas)
		{
			bool op = stus[i].change_acti(acti);
			if(!op)
				return stus[i].get_name();
		}
	}
	return "addmin";
}

string cancel_acti(string name, string clas)
{
	for(int i=1;i<=num_stu;i++)
		if(stus[i].get_class() == clas)
			stus[i].cancel_acti(name);
	return "addmin";
}

// #endif
