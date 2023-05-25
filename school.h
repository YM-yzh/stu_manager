#include "global.h"
#include "algo.h"

extern int num_buid;
extern Building buids[NUM];
extern map<string, int, greater<string>> buid_dict;

extern int num_road;
extern Road roads[NUM];

extern Graph school;

extern const string file_path;

extern ifstream info_stu;
extern string file_mkd;

extern ifstream info_schl;
extern ifstream info_buid;
extern ifstream info_road;

extern ofstream debugout;

void out_dict();
void mapinit();

void pointout(deque<Position>&path, int x);
void pathout(Path &res);
void Go(int a, int b);
