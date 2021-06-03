#include <cstdlib>
#include <iostream>
#include <vector>

#include <mmorGS.h>

bool mmorGS::createWorld(ushort height, ushort width)
{
	gs_height = height;
	gs_width = width;

	gs_grid = new char* [gs_height];
	for (ushort a{ 0 }; a < (gs_height); a++)
	{
		gs_grid[a] = new char[gs_width];
	}

	return true;
}

bool mmorGS::setTiles(uchar floorTile)
{
	gs_floorTile = floorTile;

	for (ushort a{ 0 }; a < (gs_height); a++)
	{
		for (ushort b{ 0 }; b < gs_width; b++)
		{
			gs_grid[a][b] = gs_floorTile;
		}
	}

	return true;
}

bool mmorGS::frame(ushort input, ushort finish)
{
	if (gs_isFirstFrame)
	{
		gs_isFirstFrame = false;
		draw();
	}
	else
	{
		if (input != finish)
		{
			draw();
			return true;
		}
		else
		{
			return false;
		}
	}
}

void mmorGS::draw()
{
	system("CLS");

	for (ushort a{ 0 }; a < (gs_height); a++)
	{
		for (ushort b{ 0 }; b < gs_width; b++)
		{
			std::cout << gs_grid[a][b];
		}
		std::cout << '\n';
	}
}

mmorGS::~mmorGS()
{
	for (ushort a{ 0 }; a < (gs_height); a++)
	{
		delete[] gs_grid[a];
	}
	delete[] gs_grid;
	gs_grid = nullptr;
}
