#pragma once
extern int		ROW, COL;

struct Point {
	int posX, posY;
};

enum Maptype {
	Empty = 0,
	Blocked,
	Spawn,
	Playerbase
};

bool isValid(Point const&);

class Map {
public:
	Map(int w = 12, int h = 6, int s = 30);
	~Map();

	int LoadMap(const char*);
	void DrawMap();
	int PlaceTower(Point const&);
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetBinaryValue(Point const&) const;
	int GetTowerValue(Point const&) const;

	// scale, rotate, transform

private:
	int width;
	int height;
	int scale;
	int** BinaryMap;
	int** TowerMap;
};