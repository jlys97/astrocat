#include "../Header/Main.h"

int ROW, COL;

Map::Map(int w, int h, int s) : width{ w }, height{ h }, scale{ s } {
	BinaryMap = new int* [height];
	TowerMap = new int* [height];

	for (int i = 0; i < height; ++i)
	{
		BinaryMap[i] = new int[width];
		TowerMap[i] = new int[width];
	}

	ROW = h;
	COL = w;
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
	char c;

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

int Map::PlaceTower(Point const& cell) { //add tower type enum

	if (!isValid(cell)) // check towertype exists
		return 0;

	BinaryMap[cell.posY][cell.posX] = Maptype::Blocked;
	TowerMap[cell.posY][cell.posX] = 1; // replace with tower type later
	return 1;
}

int Map::GetBinaryValue(Point const& cell) const {
	if (isValid(cell))
		return BinaryMap[cell.posY][cell.posX];
	else 
		return 0;
}

int Map::GetTowerValue(Point const& cell) const {
	if (isValid(cell))
		return TowerMap[cell.posY][cell.posX];
	else
		return 0;
}





//Utility function to check if given cell is valid
bool isValid(Point const& cell) {
	//returns true if row and column numbers are in range
	return (cell.posY >= 0) && (cell.posY < ROW) && (cell.posX >= 0) && (cell.posX < COL);
}