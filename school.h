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

void pointout(deque<Position> &path, int x);
void outpath(Path &res, ostream &xout);
void Go(int a, int b);

extern int dis[NUM][NUM];

void Floyed(int num);
