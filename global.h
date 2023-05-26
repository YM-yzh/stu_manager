#include <map>
#include <deque>
#include <vector>

#include <iomanip>
#include <fstream>
#include <iostream>

#include <string.h>
#include <algorithm>
using namespace std;

#define NUM 1004

#define Width 100
#define Legth 100

typedef map<string, int, greater<string>> maps;

extern bool admin;

extern const string file_path;
extern const string save_path;

extern string file_mkd;
extern string save_mkd;

extern ofstream debugout;
