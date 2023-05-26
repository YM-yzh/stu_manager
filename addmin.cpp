#include "addmin.h"

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

// #endif
