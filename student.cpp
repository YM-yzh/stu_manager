#include "activity.cpp"
#include "student.h"

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

bool Student::find_acti(Activity acti)
{
	vAiter targt = lower_bound(this->acti.begin(), this->acti.end(), acti);
	int left = 0;
	int right = this->acti_num;
	while(left < right)
	{
		int mid = (left + right) / 2;
		vAiter now = this->acti.begin()	+ mid;
		if (*now < acti)
			left = mid;
		else
			right = mid;
	}
}

bool Student::change_acti(Activity acti)
{
	auto targt = this->find_acti(acti.name);
	if(targt==this->acti.end())
		return false;
	*targt = acti;
	return true;
}

bool Student::cancel_acti(string name)
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
