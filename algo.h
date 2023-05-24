#include <deque>
#include <string>
#include <vector>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

// using std::deque;
// using std::string;
// using std::vector;

// int hashid(std::string str);

#define NUM 1004

#define Width 100
#define Legth 100

struct Position
{
	int x, y;
};

bool operator == (Position a, Position b)
{
	return (a.x == b.x) && (a.y == b.y);
}

void out_posi(Position a)
{
	cout << a.x << ',' << a.y << endl;
}

struct Road
{
	Position begin, end;
	void init(int x1, int y1, int x2, int y2);
};

struct Building
{
	string name;
	Position posi;
	void init(string name, int x, int y);
};

struct Path
{
	Position now;
	deque<Position> path;
};

const Path ERR = {(Position){-1, -1}};

class Graph
{
private:
	int length, width;
	int map[Width][Legth];
	bool vis[Width][Legth];
	deque<Position> path;

public:
	Graph() { memset(map, -1, sizeof(map)); }
	void set(int wid, int length);
	// void init();

	void add(int id, Position pos);
	bool add(Position begin, Position end);

	void textout(ostream& xout);
	// void pointout(int x);
	// void pathout();

	int getpoint(int x, int y);
	Path P2P(Position start, Position desti);
	bool DFS(Position start, Position desti);
	Path BFS(Position start, Position desti);
};
