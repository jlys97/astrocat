#pragma once
#include "Main.h"

class Map {
public:
	Map(int w = 12, int h = 6, int s = 30);
	~Map();

	int LoadMap(const char*);
	void DrawMap();
	int PlaceTower(int, int);
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetBinaryValue(int, int) const;
	int GetTowerValue(int, int) const;

	// scale, rotate, transform

private:
	int width;
	int height;
	int scale;
	int** BinaryMap;
	int** TowerMap;
};