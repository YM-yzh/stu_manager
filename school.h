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

struct Temp
{
	Tome tome;
	int temp_num;
	struct BB
	{
		string name, loca;
	} temp_acti[5]; // 临时事务可以同时完成

	void add(string name, string loca);
};

void pointout(deque<Position> &path, int x);
void outpath(Path &res, ostream &xout);
void Go(int a, int b);
void muilti_go(int now, Temp a);

extern int dis[NUM][NUM];

void Floyed(int num);
