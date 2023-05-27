#include "school.h"

int num_buid = 0;
Building buids[NUM] = {};
maps buid_dict;

int num_road = 0;
Road roads[NUM] = {};

Graph school = {};

void out_dict()
{
	for (auto i : buid_dict)
		debugout << i.first << ' ' << i.second << endl;
}

void mapinit()
{
	ifstream info_schl(file_path + "school/school_info.in");
	ifstream info_buid(file_path + "school/building_info.in");
	ifstream info_road(file_path + "school/road_info.in");

	int wid, len;

	info_schl >> wid >> len;
	if (wid > Width || len > Legth)
	{
		debugout << "school info error" << endl;
		cout << "学校信息错误！" << endl;
		system("pause");
		exit(0);
	}
	school.set(wid, len);

	info_schl >> num_buid;
	info_schl >> num_road;

	debugout << "school info read" << endl;
	info_schl.close();
	debugout << num_buid << ' ' << num_road << endl;

	string name;

	for (int i = 1; i <= num_buid; i++)
	{
		int x, y;
		info_buid >> name;
		info_buid >> x >> y;

		// debugout << name << ' ';
		// debugout << x << ' ' << y << endl;

		buids[i].init(name, x, y);
		buid_dict.emplace(name, i);
		school.add(i, buids[i].posi);
	}

	debugout << "building info read" << endl;
	info_buid.close();
	out_dict();

	for (int i = 1; i <= num_road; i++)
	{
		int x1, y1;
		int x2, y2;
		info_road >> x1 >> y1;
		info_road >> x2 >> y2;

		// debugout << x1 << ' ' << y1 << endl;
		// debugout << x2 << ' ' << y2 << endl;
		// debugout << i << ':' << school.width << ' ' << school.length << endl;
		roads[i].init(x1, y1, x2, y2);
		school.add(roads[i].begin, roads[i].end);
	}

	debugout << "road info read" << endl;
	info_road.close();
	debugout << "distance processing" << endl;
	Floyed(num_buid);
	debugout << "distance processed" << endl;
	school.textout(debugout);
}

void Graph::textout(ostream &xout)
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

void pointout(deque<Position> &path, int x)
{
	for (auto i : path)
	{
		int t = school.getpoint(i.x, i.y);
		if (t > 0)
		{
			cout << buids[t].name;
			if (t != x)
				cout << "->";
		}
	}
	cout << endl;
}

void outpath(Path &res, ostream &xout)
{
	xout << res.path.size() << endl;
	for (auto i : res.path)
		xout << i.x << ' ' << i.y << endl;
}

void Go(int a, int b)
{
	ofstream pathout(file_path + "path.out");
	debugout << buids[a].name << " -> " << buids[b].name << endl;
	pathsout << buids[a].name << " -> " << buids[b].name << endl;
	Path res = school.P2P(buids[a].posi, buids[b].posi);
	// res.path.push_back(res.now);
	outpath(res, pathout);
	// pointout(res.path, b);
	pathout.close();
}

void muilti_go(int now, Temp a)
{

}

int dis[NUM][NUM] = {};

void Floyed(int num)
{
	memset(dis, 114514, sizeof(dis));
	for(int i=1;i<=num;i++)
		for(int j=1;j<i;j++)
			dis[i][j]=dis[j][i]=school.BFS(buids[i].posi, buids[j].posi).path.size();
}
