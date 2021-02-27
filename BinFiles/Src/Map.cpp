#include "../Header/Map.h"

Map::Map(int w, int h, int s) : width{ w }, height{ h }, scale{ s } {
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

int Map::LoadMap(const char* filename) {
	std::fstream fs;
	fs.open(filename, std::fstream::in);

	if (!fs.is_open())
	{
		printf("Failed to retrieve file\n");
		return 0;
	}

	int rowcount = 0, columncount = 0;
	int c;

	while (rowcount < height && columncount < width)
	{
		fs >> c;
		if (c != ' ' && c != '\n')
		{
			if (c == '1')
			{
				TowerMap[rowcount][columncount] = c - '0';
				BinaryMap[rowcount][columncount] = c - '0';
			}
			else
			{
				TowerMap[rowcount][columncount] = c - '0';
				BinaryMap[rowcount][columncount] = 0;
			}

			++columncount;
			if (columncount == width)
			{
				++rowcount;
				columncount = 0;
			}

		}
	}
	fs.close();
	return 1;
}

void Map::DrawMap() {

	AEMtx33 scaling, trans, concat;

	AEMtx33Scale(&scaling, scale, scale);
	AEMtx33Trans(&trans, -width / 2, -height / 2);
	AEMtx33Concat(&concat, &trans, &scaling);

	for (int i{ 0 }; i < height; ++i)
	{
		for (int j{ 0 }; j < width; ++j)
		{
			std::cout << TowerMap[i][j];
		}
	}
}

int Map::PlaceTower(int x, int y) { //add tower type enum

	if (!isValid(x, y)) // check towertype exists
		return 0;

	BinaryMap[y][x] = 1;
	TowerMap[y][x] = 1; // replace with tower type later
	return 1;
}

int Map::GetBinaryValue(int x, int y) const {
	if (isValid(x, y))
		return BinaryMap[y][x];
	else 
		return 0;
}

int Map::GetTowerValue(int x, int y) const {
	if (isValid(x, y))
		return TowerMap[y][x];
	else
		return 0;
}





//Utility function to check if given cell is valid
bool isValid(int row, int col) {
	//returns true if row and column numbers are in range
	return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}