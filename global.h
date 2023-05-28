#pragma once
#include <map>
#include <utility>
#include <deque>
#include <vector>

#include <iomanip>
#include <fstream>
#include <iostream>

#include <string.h>
#include <algorithm>
using namespace std;

#define NUM 204

#define Width 100
#define Legth 100

#define bEgin 6
#define eNd 22

#define DISMAX 1e6 +7

typedef map<string, int, greater<string>> maps;

// extern bool admin;

extern const string file_path;
extern const string save_path;

extern string file_mkd;
extern string save_mkd;

extern ofstream debugout;
extern ofstream pathsout;
