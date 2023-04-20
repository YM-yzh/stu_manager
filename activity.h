#include "school.h"

struct Time
{
	int day; // 表示星期
	// int month, day;
	// int hour, minute;
	// int frequency;
	int hour; // 以小时为单位进行活动
};

class Activity // 学生活动信息
{
private:
	string name;
	Time begin, end;
	int last; // 持续时长
	Position location;
	bool form; // 0表示线下，1表示线上
public:
	void init_activity(string nam, Time begin, Time end, Position loc, bool op);
	void change_activity(string nam, Time begin, Time end, Position loc, bool op);
	void cancel_activity(string nam);
};
