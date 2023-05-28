#pragma once
#include "global.h"
#include "algo.h"

extern int num_buid;
extern Building buids[NUM];
extern maps buid_dict;

extern int num_road;
extern Road roads[NUM];

extern Graph school;

void out_dict();
void mapinit();

struct Tome
{
	int day;  // 表示星期
	int hour; // 以小时为单位进行活动

	int nextime();
	void nextday();
	void outime(ostream &xout);
	void putime(ostream &xout);
};

struct Temp
{
	Tome tome;
	int num;
	struct BB
	{
		string name, loca;
	} temp_acti[5]; // 临时事务可以同时完成

	void add(string name, string loca);
};

void pointout(deque<Position> &path, int x);
void outpath(Path &res, ostream &xout);
void Go(int a, int b);
void multi_go(int now, Temp a);

extern int dis[NUM][NUM];

void Floyed(int num);
