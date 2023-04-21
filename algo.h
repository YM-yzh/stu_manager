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

#define NUM 1004

#define Width 100
#define Length 100

template <typename T>
void respwan(T &a, T &b)
{
	T c;
	c = a;
	a = b;
	b = c;
};
// int hashid(std::string str);

struct Position
{
	int x, y;
};

void out_posi(Position a)
{
	cout << a.x << a.y << endl;
}

bool operator == (Position a, Position b)
{
	return (a.x == b.x) && (a.y == b.y);
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

class Graph
{
private:
	int length, width;
	int map[Width][Length];
	bool vis[Width][Length];
	deque<Position> path;

public:
	Graph() { memset(map, -1, sizeof(map)); }
	void set(int wid, int length);
	// void init();

	void add(int id, Position pos);
	bool add(Position begin, Position end);

	void textout();
	void pathout();
	bool P2P(Position start, Position desti);
	bool DFS(Position start, Position desti);
};

void Graph::set(int wid, int len)
{
	this->width = wid;
	this->length = len;
	memset(this->map, -1, sizeof(this->map));
}

void Graph::add(int id, Position pos)
{
	this->map[pos.x][pos.y] = id;
}

bool Graph::add(Position begin, Position end)
{
	if (begin.x != end.x && begin.y != end.y)
		return false;
	if (begin.x > end.x || begin.y > end.y)
		respwan(begin, end);
	for (int i = begin.x; i <= end.x; i++)
		for (int j = begin.y; j <= end.y; j++)
			if (this->map[i][j] == -1)
				this->map[i][j] = 0;
	return true;
}

const int X[4] = {-1, 1, 0, 0};
const int Y[4] = { 0, 0, 1,-1};

bool Graph::P2P(Position start, Position desti)
{
	memset(this->vis, false, sizeof(this->vis));
	while(this->path.size())
		this->path.pop_back();
	return this->DFS(start, desti);
}

bool Graph::DFS(Position start, Position desti)
{
	if(start.x <= 0 || start.x >= this->width || start.y <= 0 || start.y >= this->length)
		return false;
	if(this->vis[start.x][start.y] || this->map[start.x][start.y]==-1)
		return false;
	this->vis[start.x][start.y]=true;
	if(start == desti)
	{
		this->path.push_front(start);
		return true;
	}
	for(int i=0;i<4;i++)
	{
		Position now;
		now.x=start.x+X[i];
		now.y=start.y+Y[i];
		bool f = this->DFS(now, desti);
		if(f)
		{
			this->path.push_front(start);
			return true;
		}
	}
	return false;
}
/*
Path Graph::BFS(Position start, Position desti)
{
	deque<Path> q;
	Path a;
	memset(this->vis, false, sizeof(this->vis));

	a.now = start;
	q.push_back(a);
	while (q.size())
	{
		a = q.front();
		q.pop_front();
		vis[a.now.x][a.now.y] = true;
		out_posi(a.now);
		if (a.now == desti)
		{
			a.path.push_back(a.now);
			return a;
		}
		for (int i = 0; i < 3; i++)
		{
			Path b = a;
			b.now.x += X[i];
			b.now.y += Y[i];
			if (!vis[b.now.x][b.now.y] && this->map[b.now.x][b.now.y] != -1)
			{
				b.path.push_back(a.now);
				q.push_back(b);
			}
		}
	}
	return ERR;
}
*/
void Road::init(int x1, int y1, int x2, int y2)
{
	this->begin = (Position){x1, y1};
	this->end = (Position){x2, y2};
}

void Building::init(string name, int x, int y)
{
	this->name = name;
	this->posi = (Position){x, y};
}
