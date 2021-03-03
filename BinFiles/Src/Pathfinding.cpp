#include "../Header/Map.h"
#include "../Header/Pathfinding.h"
#include <iostream>
#include <algorithm>

bool isUnblocked(Map const& map, Point const& cell)
{
	if (map.GetBinaryValue(cell) == 0)
		return true;
	return false;
}

bool isDestination(Point const& src, Point const& dest)
{
	if (src.posX == dest.posX && src.posY == dest.posY)
		return true;
	return false;
}

double calculateHvalue(Point const& src, Point const& dest)
{
	double D = 1;
	double D2 = 1.4;

	double dx = abs(src.posX - dest.posX);
	double dy = abs(src.posY - dest.posY);
	double dmax = std::max(dx, dy);
	double dmin = std::min(dx, dy);

	return (D2 * dmin + D * (dmax - dmin));
}

void tracePath(std::vector<std::vector<Node>> cell, Point const& dest, Map& map)
{
	int row = dest.posY;
	int col = dest.posX;

	std::vector<Point> Path;
	//std::cout << "Tracing Path\n";

	while (!(cell[row][col].parent.posX == col && cell[row][col].parent.posY == row))
	{
		std::cout << "Trace\n";
		Path.push_back(Point{ col, row });
		std::cout << row << "," << col << "\n";
		int tmprow = cell[row][col].parent.posY;
		int tmpcol = cell[row][col].parent.posX;
		row = tmprow;
		col = tmpcol;
		//std::cout << row << col << "\n";
	}
	//std::cout << "Traced Path\n";

	Path.push_back(Point{ col, row });
	while (!Path.empty())
	{
		Point p = Path.front();
		Path.erase(Path.begin());
		map.PlaceTower(p);
	}
	return;
}

void astar(Map& map, Point const& src, Point const& dest)
{
	// if source is out of range
	if (isValid(src) == false)
	{
		std::cout << "Out of range";
		return;
	}

	// if destination is out of range
	if (isValid(dest) == false)
	{
		std::cout << "Out of range";
		return;
	}

	// if source or destination is blocked
	if (isUnblocked(map, src) == false || isUnblocked(map, dest) == false)
	{
		std::cout << "Blocked";
		return;
	}

	// if already at destination
	if (isDestination(src, dest) == true)
	{
		std::cout << "Already at destination";
		return;
	}

	std::vector<bool> line(COL, false);
	std::vector<std::vector<bool>> ClosedList(ROW, line);

	std::vector<std::vector<Node>> CellDetails(ROW, std::vector<Node>(COL));

	for (int i{ 0 }; i < ROW; ++i) {
		for (int j{ 0 }; j < COL; ++j) {
			ClosedList[i][j] = false;
			CellDetails[i][j].f = static_cast<double>(MAX::MaxCost);
			CellDetails[i][j].g = static_cast<double>(MAX::MaxCost);
			CellDetails[i][j].h = static_cast<double>(MAX::MaxCost);
			CellDetails[i][j].parent = { -1, -1 };
		}
	}
	//std::cout << "Initialized\n";

	int i{ src.posY }, j{ src.posX };
	CellDetails[i][j].f = 0.0;
	CellDetails[i][j].g = 0.0;
	CellDetails[i][j].h = 0.0;
	CellDetails[i][j].parent = { j, i };
	//std::cout << i << j << "\n*" << CellDetails[i][j].parent.posY << CellDetails[i][j].parent.posX << "\n";

	std::vector<List> OpenList;

	OpenList.emplace_back(List{ 0.0, src });

	bool foundDest{ false };

	//std::cout << "Check destination\n";

	while (!OpenList.empty()) {
		List p = *OpenList.begin();

		OpenList.erase(OpenList.begin());

		i = p.start.posY;
		j = p.start.posX;
		ClosedList[i][j] = true;

		//std::cout << i << j << "\n";

		double gNew, hNew, fNew;

		//std::cout << "Debug Me\n";

		int x = -1, y = 0;

		if (isValid(Point{ j + x, i + y }) == true) {
			if (isDestination(Point{ j + x, i + y }, dest) == true) {
				CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
				//std::cout << "Trace Path ";
				tracePath(CellDetails, dest, map);
				foundDest = true;
				std::cout << "Found Destination\n";
				return;
			}
			else if (ClosedList[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)] == false
				&& isUnblocked(map, Point{ j + x, i + y }) == true) {
				gNew = CellDetails[i][j].g + 1.0;
				hNew = calculateHvalue(Point{ j + x, i + y }, dest);
				fNew = gNew + hNew;

				if (CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f == MAX::MaxCost
					|| CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f > fNew) {
					List Listnew{ fNew, Point{ j + x, i + y } };
					OpenList.emplace_back(Listnew);

					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f = fNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].g = gNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].h = hNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
					std::cout << i + y << " " << j + x << "\n" << CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posY << " | "
						<< CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posX << "\n";
					std::cout << hNew << "\n";
				}
				std::cout << "Loop Hell\n";
			}
		}
		x = 1;
		y = 0;
		if (isValid(Point{ j + x, i + y }) == true) {
			if (isDestination(Point{ j + x, i + y }, dest) == true) {
				CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
				//std::cout << "Trace Path ";
				tracePath(CellDetails, dest, map);
				foundDest = true;
				std::cout << "Found Destination\n";
				return;
			}
			else if (ClosedList[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)] == false
				&& isUnblocked(map, Point{ j + x, i + y }) == true) {
				gNew = CellDetails[i][j].g + 1.0;
				hNew = calculateHvalue(Point{ j + x, i + y }, dest);
				fNew = gNew + hNew;

				if (CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f == MAX::MaxCost
					|| CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f > fNew) {
					List Listnew{ fNew, Point{ j + x, i + y } };
					OpenList.emplace_back(Listnew);

					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f = fNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].g = gNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].h = hNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
					std::cout << i + y << " " << j + x << "\n" << CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posY << " | "
						<< CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posX << "\n";
					std::cout << hNew << "\n";
				}
				std::cout << "Loop Hell\n";
			}
		}
		x = 0;
		y = -1;
		if (isValid(Point{ j + x, i + y }) == true) {
			if (isDestination(Point{ j + x, i + y }, dest) == true) {
				CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
				//std::cout << "Trace Path ";
				tracePath(CellDetails, dest, map);
				foundDest = true;
				std::cout << "Found Destination\n";
				return;
			}
			else if (ClosedList[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)] == false
				&& isUnblocked(map, Point{ j + x, i + y }) == true) {
				gNew = CellDetails[i][j].g + 1.0;
				hNew = calculateHvalue(Point{ j + x, i + y }, dest);
				fNew = gNew + hNew;

				if (CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f == MAX::MaxCost
					|| CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f > fNew) {
					List Listnew{ fNew, Point{ j + x, i + y } };
					OpenList.emplace_back(Listnew);

					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f = fNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].g = gNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].h = hNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
					std::cout << i + y << " " << j + x << "\n" << CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posY << " | "
						<< CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posX << "\n";
					std::cout << hNew << "\n";
				}
				std::cout << "Loop Hell\n";
			}
		}
		x = 0;
		y = 1;
		if (isValid(Point{ j + x, i + y }) == true) {
			if (isDestination(Point{ j + x, i + y }, dest) == true) {
				CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
				//std::cout << "Trace Path ";
				tracePath(CellDetails, dest, map);
				foundDest = true;
				std::cout << "Found Destination\n";
				return;
			}
			else if (ClosedList[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)] == false
				&& isUnblocked(map, Point{ j + x, i + y }) == true) {
				gNew = CellDetails[i][j].g + 1.0;
				hNew = calculateHvalue(Point{ j + x, i + y }, dest);
				fNew = gNew + hNew;

				if (CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f == MAX::MaxCost
					|| CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f > fNew) {
					List Listnew{ fNew, Point{ j + x, i + y } };
					OpenList.emplace_back(Listnew);

					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f = fNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].g = gNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].h = hNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
					std::cout << i + y << " " << j + x << "\n" << CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posY << " | "
						<< CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posX << "\n";
					std::cout << hNew << "\n";
				}
				std::cout << "Loop Hell\n";
			}
		}
		x = -1;
		y = -1;
		if (isValid(Point{ j + x, i + y }) == true) {
			if (isDestination(Point{ j + x, i + y }, dest) == true) {
				CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
				//std::cout << "Trace Path ";
				tracePath(CellDetails, dest, map);
				foundDest = true;
				std::cout << "Found Destination\n";
				return;
			}
			else if (ClosedList[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)] == false
				&& isUnblocked(map, Point{ j + x, i + y }) == true) {
				gNew = CellDetails[i][j].g + 1.0;
				hNew = calculateHvalue(Point{ j + x, i + y }, dest);
				fNew = gNew + hNew;

				if (CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f == MAX::MaxCost
					|| CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f > fNew) {
					List Listnew{ fNew, Point{ j + x, i + y } };
					OpenList.emplace_back(Listnew);

					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f = fNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].g = gNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].h = hNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
					std::cout << i + y << " " << j + x << "\n" << CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posY << " | "
						<< CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posX << "\n";
					std::cout << hNew << "\n";
				}
				std::cout << "Loop Hell\n";
			}
		}
		x = -1;
		y = 1;
		if (isValid(Point{ j + x, i + y }) == true) {
			if (isDestination(Point{ j + x, i + y }, dest) == true) {
				CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
				//std::cout << "Trace Path ";
				tracePath(CellDetails, dest, map);
				foundDest = true;
				std::cout << "Found Destination\n";
				return;
			}
			else if (ClosedList[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)] == false
				&& isUnblocked(map, Point{ j + x, i + y }) == true) {
				gNew = CellDetails[i][j].g + 1.0;
				hNew = calculateHvalue(Point{ j + x, i + y }, dest);
				fNew = gNew + hNew;

				if (CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f == MAX::MaxCost
					|| CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f > fNew) {
					List Listnew{ fNew, Point{ j + x, i + y } };
					OpenList.emplace_back(Listnew);

					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f = fNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].g = gNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].h = hNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
					std::cout << i + y << " " << j + x << "\n" << CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posY << " | "
						<< CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posX << "\n";
					std::cout << hNew << "\n";
				}
				std::cout << "Loop Hell\n";
			}
		}
		x = 1;
		y = -1;
		if (isValid(Point{ j + x, i + y }) == true) {
			if (isDestination(Point{ j + x, i + y }, dest) == true) {
				CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
				//std::cout << "Trace Path ";
				tracePath(CellDetails, dest, map);
				foundDest = true;
				std::cout << "Found Destination\n";
				return;
			}
			else if (ClosedList[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)] == false
				&& isUnblocked(map, Point{ j + x, i + y }) == true) {
				gNew = CellDetails[i][j].g + 1.0;
				hNew = calculateHvalue(Point{ j + x, i + y }, dest);
				fNew = gNew + hNew;

				if (CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f == MAX::MaxCost
					|| CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f > fNew) {
					List Listnew{ fNew, Point{ j + x, i + y } };
					OpenList.emplace_back(Listnew);

					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f = fNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].g = gNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].h = hNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
					std::cout << i + y << " " << j + x << "\n" << CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posY << " | "
						<< CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posX << "\n";
					std::cout << hNew << "\n";
				}
				std::cout << "Loop Hell\n";
			}
		}
		x = 1;
		y = 1;
		if (isValid(Point{ j + x, i + y }) == true) {
			if (isDestination(Point{ j + x, i + y }, dest) == true) {
				CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
				//std::cout << "Trace Path ";
				tracePath(CellDetails, dest, map);
				foundDest = true;
				std::cout << "Found Destination\n";
				return;
			}
			else if (ClosedList[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)] == false
				&& isUnblocked(map, Point{ j + x, i + y }) == true) {
				gNew = CellDetails[i][j].g + 1.0;
				hNew = calculateHvalue(Point{ j + x, i + y }, dest);
				fNew = gNew + hNew;

				if (CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f == MAX::MaxCost
					|| CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f > fNew) {
					List Listnew{ fNew, Point{ j + x, i + y } };
					OpenList.emplace_back(Listnew);

					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].f = fNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].g = gNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].h = hNew;
					CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent = { j, i };
					std::cout << i + y << " " << j + x << "\n" << CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posY << " | "
						<< CellDetails[static_cast<size_t>(i) + static_cast<size_t>(y)][static_cast<size_t>(j) + static_cast<size_t>(x)].parent.posX << "\n";
					std::cout << hNew << "\n";
				}
				std::cout << "Loop Hell\n";
			}
		}
	}

	if (foundDest == false)
		std::cout << "Failed to find destination cell\n";
	return;
}