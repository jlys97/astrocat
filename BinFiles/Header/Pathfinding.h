#pragma once
#include "Map.h"
#include <vector>

struct Node {
	Point curr, parent;
	double f, g, h;
};

struct List {
	double cost;
	Point start;
};

enum MAX {
	MaxCost = 20000;
};

bool isUnblocked(Map const&, Point const&);
bool isDestination(Point const&, Point const&);
double calculateHvalue(Point const&, Point const&);
void tracePath(std::vector<std::vector<Node>>, Point const&);
