#include <iomanip>
#include <fstream>
using namespace std;

const string file_path = "./cache/";
ifstream info_schl(file_path + "school/school_info.in");
ifstream info_buid(file_path + "school/building_info.in");
ifstream info_road(file_path + "school/road_info.in");

ofstream debugout("./test.out");

void mapchange()
{
	int wid, len;
	int num_buid, num_road;

	info_schl >> wid >> len;

	info_schl >> num_buid;
	info_schl >> num_road;

	debugout << num_buid << endl << num_road << endl;

	string name;

	for (int i = 1; i <= num_buid; i++)
	{
		int x, y;
		info_buid >> name;
		info_buid >> x >> y;

		debugout << name << ' ';
		debugout << x+1 << ' ' << y+1 << endl;
	}

	// out_dict();

	for (int i = 1; i <= num_road; i++)
	{
		int x1, y1;
		int x2, y2;
		info_road >> x1 >> y1;
		info_road >> x2 >> y2;

		debugout << x1+1 << ' ' << y1+1 << ' ';
		debugout << x2+1 << ' ' << y2+1 << endl;
	}
}

int main()
{
	mapchange();
	return 0;
}
