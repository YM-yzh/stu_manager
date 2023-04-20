#include "algo.h"

#include <map>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <iostream>

int num_buid;
Building buids[NUM];
map<string, int, greater<string>> dict;

int num_road;
Road roads[NUM];

Graph school;

ifstream info_schl("./testin/school_info.in");
ifstream info_buid("./testin/building_info.in");
ifstream info_road("./testin/road_info.in");
ifstream info_stu("./testin/student_info.in");

ofstream testout("./test.out");
void out_dict()
{
	for (auto i : dict)
		testout << i.first << ' ' << i.second << endl;
}

void mapinit()
{
	int wid, len;

	info_schl >> wid >> len;
	school.set(wid, len);

	info_schl >> num_buid;
	info_schl >> num_road;

	// testout << num_buid << ' ' << num_road << endl;

	string name;

	for (int i = 1; i <= num_buid; i++)
	{
		int x, y;
		info_buid >> name;
		info_buid >> x >> y;

		// testout << name << ' ';
		// testout << x << ' ' << y << endl;

		buids[i].init(name, x, y);
		dict.emplace(name, i);
		school.add(i, buids[i].posi);
	}

	// out_dict();

	for (int i = 1; i <= num_road; i++)
	{
		int x1, y1;
		int x2, y2;
		info_road >> x1 >> y1;
		info_road >> x2 >> y2;

		// testout << x1 << ' ' << y1 << endl;
		// testout << x2 << ' ' << y2 << endl;

		roads[i].init(x1, y1, x2, y2);
		school.add(roads[i].begin, roads[i].end);
	}

	school.textout();
}

void Graph::textout()
{
	int wid = this->width;
	int len = this->length;
	for (int i = 1; i <= wid; i++)
	{
		for (int j = 1; j <= len; j++)
			testout << setw(4) << setfill(' ') << this->map[i][j];
		testout << endl;
	}
}

void Graph::pathout()
{
	for(auto i : this->path)
		testout << '(' << i.x << ',' << i.y << ')' << endl;
}

void Go(int a, int b)
{
	bool flag = school.P2P(buids[a].posi, buids[b].posi);
	// school.pathout();
}

void stutest()
{
	int num_reqs;
	string a, b;

	info_schl >> num_reqs;

	for (int i = 1; i <= num_reqs; i++)
	{
		info_stu >> a >> b;
		int aid = dict[a];
		int bid = dict[b];

		testout << i << endl;
		Go(aid, bid);
		testout << endl;
	}
}

void stuinit()
{
	int num_reqs;
	string a, b;

	info_schl >> num_reqs;

	for (int i = 1; i <= num_reqs; i++)
	{
		info_stu >> a >> b;
		int aid = dict[a];
		int bid = dict[b];

		testout << i << endl;
		Go(aid, bid);
		testout << endl;
	}
}
