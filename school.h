#include "algo.h"

#include <map>

#include <iomanip>
#include <fstream>

int num_buid;
Building buids[NUM];
map<string, int, greater<string>> buid_dict;

int num_road;
Road roads[NUM];

Graph school;

const string file_path = "./testin/";
ifstream info_schl(file_path + "school/school_info.in");
ifstream info_buid(file_path + "school/building_info.in");
ifstream info_road(file_path + "school/road_info.in");

ofstream testout("./test.out");
void out_dict()
{
	for (auto i : buid_dict)
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
		buid_dict.emplace(name, i);
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

	school.textout(testout);
}

void Graph::textout(ostream& xout)
{
	int wid = this->width;
	int len = this->length;
	for (int i = 1; i <= wid; i++)
	{
		for (int j = 1; j <= len; j++)
			xout << setw(4) << setfill(' ') << this->map[i][j];
		xout << endl;
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
