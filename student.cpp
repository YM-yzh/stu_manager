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

vAiter Student::begin()
{
	return this->acti.begin();
}

vAiter Student::end()
{
	return this->acti.end();
}

string Student::get_user()
{
	return this->user;
}

string Student::get_name()
{
	return this->name;
}

string Student::get_id()
{
	return this->id;
}

string Student::get_class()
{
	return this->clas;
}

string Student::get_domi()
{
	return this->domi;
}

void Student::nextday(int day, vAiter begin)
{
	day = day % 7 + 1;
	cout << "星期" << week[day] << endl;
	for (auto i = begin; i != this->end(); i++)
	{
		if (i->tome.day < day)
			continue;
		if (i->tome.day > day)
			break;
		cout << setw(2) << setfill(' ') << i->tome.hour << "点 ~ ";
		cout << setw(2) << setfill(' ') << i->tome.hour + i->last << "点 ";
		cout << i->loca << ' ' << i->name << endl;
	}
}

void Student::move(string &loca)
{
	int aid = this->now;
	int bid = buid_dict[loca];
	if (aid != bid)
		Go(aid, bid);
	this->now = bid;
}

void Student::rest()
{
	this->move(this->domi);
}

int Student::get_Location()
{
	return this->now;
}

void Student::init_activity(ifstream &less, ifstream &acti)
{
	// ss >> this->acti_num;
	Activity x;
	for (int i = 1; i <= less_num; i++)
	{
		x.read(less);
		this->acti.push_back(x);
		// this->acti_dict.emplace(x.name, i-1);
	}
	for (int i = 1; i <= acti_num; i++)
	{
		x.read(acti);
		this->acti.push_back(x);
		// this->acti_dict.emplace(x.name, i-1);
	}
	sort(this->acti.begin(), this->acti.end());
	// actiout(this->acti);
}

void Student::save_activity(ostream &less, ostream &acti)
{
	less << this->less_num << endl;
	acti << this->acti_num - this->less_num << endl;
	for (auto i : this->acti)
	{
		if (i.kind > 3)
			i.write(less);
		if (i.kind < 3)
			i.write(acti);
	}
}

void Student::nless(int num)
{
	this->less_num = num;
}

void Student::nacti(int num)
{
	this->acti_num = num;
}

void Student::merge()
{
	this->acti_num += this->less_num;
}

vA Student::find_acti(int kind)
{
	vA res = {};
	for (auto i : this->acti)
		if (i.kind == kind)
			res.push_back(i);
	return res;
}

vAiter Student::find_acti(Tome tome)
{
	Activity x = {};
	x.tome = tome;
	auto res = this->find_acti(x);
	if (res->tome == tome)
		return res;
	return this->end();
}

vAiter Student::find_acti(string name)
{
	for (vAiter i = this->begin(); i != this->end(); i++)
	{
		// debugout << i->name << name << endl;
		if (i->name == name)
			return i;
	}
	return this->end();
}

bool opbefore(vAiter tar, Activity acti)
{
	Activity l = *tar;
	return (l.tome + l.last) <= (acti.tome);
}

bool opins(vAiter tar, Activity acti)
{
	Activity l = *tar;
	for (tar++; tar->kind == 3; tar++);
	Activity r = *tar;
	return (l.tome + l.last) <= (acti.tome) && (acti.tome + acti.last) <= r.tome;
}

bool opafter(vAiter tar, Activity acti)
{
	for (tar++; tar->kind == 3; tar++);
	Activity r = *tar;
	return (acti.tome + acti.last) <= r.tome;
}

vAiter Student::find_acti(Activity acti)
{
	// vAiter targt = lower_bound(this->acti.begin(), this->acti.end(), acti);
	int left = 0;
	int right = this->acti_num - 1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		vAiter now = this->acti.begin() + mid;
		if ((*now) <= acti)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return this->acti.begin() + left - 1;
}

vT Student::insert_acti(Activity acti)
{
	vT feb = {};
	pTT pp;
	pp.first = pp.second = (Tome){0, 0};
	feb.push_back(pp);

	auto targt = this->find_acti(acti);
	bool flag;
	if(targt + 1 == this->begin())
		flag = opafter(targt + 1, acti);
	if(targt == this->end())
		flag = opbefore(targt --, acti);
	else
		flag = opins(targt, acti);
	if (flag)
	{
		if (acti.kind == 1)
		{

		}
		else
		{
			this->acti.insert(targt + 1, acti);
			this->acti_num++;
			if (acti.kind > 3)
				this->less_num++;
		}
		return feb;
	}
	feb.pop_back();

	Tome begin = (Tome){targt->tome.day, 6};
	for (auto pre = targt - 1; pre->tome.day == targt->tome.day; targt--, pre = targt - 1);
	for (auto now = targt; targt->tome.day == now->tome.day; targt++)
	{
		if (targt->kind == 3)
			continue;
		if (targt->tome.hour - begin.hour >= acti.last)
		{
			pp.first = begin;
			pp.second = targt->tome;
			feb.push_back(pp);
		}
		begin = targt->tome + targt->last;
	}
	if (begin.hour < eNd)
	{
		pp.first = begin;
		pp.second = (Tome){begin.day, eNd};
		feb.push_back(pp);
	}
	begin = targt->tome + targt->last;
	return feb;
}

vT Student::change_acti(Activity acti)
{
	this->cancel_acti(acti.name);
	return this->insert_acti(acti); // 为了维护有序序列，先取消原有日程，再添加
}

bool Student::cancel_acti(string name)
{
	auto targt = this->find_acti(name);
	if (targt == this->end())
		return false;
	this->acti.erase(targt);
	return true;
}

vAiter Student::erase_acti(vAiter targt)
{
	auto res = this->acti.erase(targt);
	this->acti_num--;
	if (targt->kind > 3)
		this->less_num--;
	return res;
}

bool Student::add_alarm(Activity acti, Tome tome, int freq)
{
	Activity alarm = acti;
	alarm.kind = 3;
	alarm.name = "闹钟" + name;
	alarm.that = alarm.tome;
	alarm.tome = tome;
	alarm.last = 0;
	alarm.freq = freq;
	auto res = this->insert_acti(alarm);
	return res.begin()->first.day == 0;
}

void Student::textout(ostream &xout)
{
	xout << this->user << endl;
	xout << this->name << ' ' << this->id << ' ' << this->pass << ' ' << this->domi << endl;
	xout << this->acti_num << endl;
	for (auto i : this->acti)
		i.textout(xout);
}

void Student::save(ostream &xout)
{
	xout << this->name << endl;
	xout << this->id << endl;
	xout << this->clas << endl;
	xout << this->pass << endl;
	xout << this->domi << endl;
}

void actiout(vector<Activity> x)
{
	for (auto i : x)
		debugout << i.name << endl;
}

void stuinit()
{
	ifstream info_stu(file_path + "student/student_info.in");
	info_stu >> num_stu;
	if (num_stu > NUM)
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
	ifstream info_less, info_acti;
	int num;
	for (int i = 1; i <= num_stu; i++)
	{
		info_stu >> ss;
		info_ss.open(file_mkd + ss + "/_info.in");

		info_ss >> name >> id >> clas >> pass >> domi;
		stus[i].init(ss, name, id, clas, pass, domi);
		// stus_dict.emplace(id, i);
		stus_dict.emplace(ss, i);
		debugout << ss << " info read" << endl;
		info_ss.close();

		info_less.open(file_mkd + ss + "/lesson.in");
		info_acti.open(file_mkd + ss + "/activity.in");

		info_less >> num;
		stus[i].nless(num);
		info_acti >> num;
		stus[i].nacti(num);

		stus[i].init_activity(info_less, info_acti);

		debugout << ss << " lesson read" << endl;
		debugout << ss << " activity read" << endl;
		info_less.close();
		info_acti.close();

		stus[i].merge();
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
	ofstream save_less, save_acti;
	for (int i = 1; i <= num_stu; i++)
	{
		info_stu >> ss;
		save_ss.open(save_mkd + ss + "/_info.in");

		Student stu = stus[i];
		stu.save(save_ss);
		debugout << ss << " info saved" << endl;
		save_ss.close();

		save_less.open(save_mkd + ss + "/lesson.in");
		save_acti.open(save_mkd + ss + "/activity.in");

		stus[i].save_activity(save_less, save_acti);

		debugout << ss << " lesson saved" << endl;
		debugout << ss << " activity saved" << endl;
		save_less.close();
		save_acti.close();
	}
	info_stu.close();
}

// #ifdef ADMIN

string add_acti(Activity acti, string clas)
{
	for (int i = 1; i <= num_stu; i++)
	{
		if (stus[i].get_class() == clas)
		{
			auto op = stus[i].insert_acti(acti);
			if (op.begin()->first.day > 0)
				return stus[i].get_name();
		}
	}
	return "addmin";
}

string change_acti(Activity acti, string clas)
{
	for (int i = 1; i <= num_stu; i++)
	{
		if (stus[i].get_class() == clas)
		{
			auto op = stus[i].change_acti(acti);
			if (op.begin()->first.day > 0)
				return stus[i].get_name();
		}
	}
	return "addmin";
}

string cancel_acti(string name, string clas)
{
	for (int i = 1; i <= num_stu; i++)
	{
		if (stus[i].get_class() == clas)
		{
			auto op = stus[i].cancel_acti(name);
			if (!op)
				return stus[i].get_name();
		}
	}
	return "addmin";
}

// #endif
