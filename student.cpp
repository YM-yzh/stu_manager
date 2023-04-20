#include <iostream>
#include "student.h"

void Student::set_id(int newid)
{
	this->id = newid;
}

int Student::get_id()
{
	return this->id;
}

void Stu_Position::set_posi(Position newloc)
{
	this->now = newloc;
}

Position Stu_Position::get_posi()
{
	return this->now;
}

int main()
{

	return 0;
}
