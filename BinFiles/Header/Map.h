#pragma once
class Map {
public:
	Map(int w = 12, int h = 6);
	~Map();

	void LoadMap();
	void DrawMap();

private:
	int width;
	int height;
	static int** BinaryMap;
	static int** TowerMap;
};