#include <string>
#include "activity.h"
using std::string;

class Student // 学生基本信息
{
private:
	int id;
	string name;
	Position now;

public:
	void set_id(int newid);
	void set_name(string str);
	int get_id();
	void set_location(Position newloc);
	Position get_Location();
};

void Student::set_id(int newid)
{
	this->id = newid;
}

int Student::get_id()
{
	return this->id;
}

void Student::set_location(Position newloc)
{
	this->now = newloc;
}

Position Student::get_Location()
{
	return this->now;
}
