#include "../Header/Map.h"

//class Map {
//public:
//	Map(int w = 12, int h = 6);
//	~Map();
//
//	void LoadMap(int**);
//	void DrawMap();
//
//private:
//	int width;
//	int height;
//	static int** BinaryMap;
//	static int** TowerMap;
//};

Map::Map(int w, int h) : width{ w }, height{ h } 
{
	BinaryMap = new int* [height];
	TowerMap = new int* [height];

	for (int i = 0; i < height; ++i)
	{
		BinaryMap[i] = new int[width];
		TowerMap[i] = new int[width];
	}
}

Map::~Map() {
	for (int i = 0; i < height; ++i)
	{
		delete[] BinaryMap[i];
		delete[] TowerMap[i];
	}
	delete[] BinaryMap;
	delete[] TowerMap;
}

void Map::LoadMap() {

}

void Map::DrawMap() {

}