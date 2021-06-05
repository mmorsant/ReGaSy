#include <cstdlib>
#include <iostream>
#include <vector>

#include <mmorGS.h>

bool mmorGS::createWorld(ushort height, ushort width)
{
	gs_height = height;
	gs_width = width;

	gs_grid = new uchar* [gs_height];
	for (ushort a{ 0 }; a < (gs_height); a++)
	{
		gs_grid[a] = new uchar[gs_width];
	}

	return true;
}

void mmorGS::setTiles(uchar floorTile, uchar wallTile)
{
	gs_floorTile = floorTile;
	gs_wallTile = wallTile;

	for (ushort a{ 0 }; a < gs_height; a++)
	{
		for (ushort b{ 0 }; b < gs_width; b++)
		{
			gs_grid[a][b] = gs_floorTile;
		}
	}

	//outter up wall
	for (ushort a{ 0 }; a < gs_width; a++)
	{
		gs_grid[0][a] = gs_wallTile;
	}
	//outter down wall
	for (ushort a{ 0 }; a < gs_width; a++)
	{
		gs_grid[(gs_height - 1)][a] = gs_wallTile;
	}
	//outter left wall
	for (ushort a{ 0 }; a < gs_height; a++)
	{
		gs_grid[a][0] = gs_wallTile;
	}
	//outter right wall
	for (ushort a{ 0 }; a < gs_height; a++)
	{
		gs_grid[a][(gs_width - 1)] = gs_wallTile;
	}
}

bool mmorGS::spawnPlayer(uchar tile, ushort posY, ushort posX)
{
	gs_playerTile = tile;

	gs_playerPosY = posY;
	gs_playerPosX = posX;

	gs_grid[gs_playerPosY][gs_playerPosX] = gs_playerTile;

	return true;
}

void mmorGS::setPlayerLife(uint amountLife)
{
	gs_playerLife = amountLife;
}

void mmorGS::setKeys(uchar upKey, uchar downKey, uchar leftKey, uchar rightKey)
{
	gs_upKey = upKey;
	gs_downKey = downKey;
	gs_leftKey = leftKey;
	gs_rightKey = rightKey;
}

bool mmorGS::frame(uchar input, uchar finish)
{
	if (gs_isFirstFrame)
	{
		gs_isFirstFrame = false;
		draw();
		return true;
	}
	else
	{
		if (input != finish)
		{
			if (!(collision(input, gs_wallTile)))
			{
				movePlayer(input);
			}
			else
				NULL;
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

	for (ushort a{ 0 }; a < gs_height; a++)
	{
		for (ushort b{ 0 }; b < gs_width; b++)
		{
			std::cout << gs_grid[a][b];
		}
		std::cout << '\n';
	}

	std::cout << "Player Life: " << gs_playerLife << '\n';
}

bool mmorGS::movePlayer(uchar input)
{
	if (input == gs_upKey)
	{
		gs_grid[gs_playerPosY][gs_playerPosX] = gs_floorTile;
		gs_playerPosY--;
	}
	else if (input == gs_downKey)
	{
		gs_grid[gs_playerPosY][gs_playerPosX] = gs_floorTile;
		gs_playerPosY++;
	}
	else if (input == gs_leftKey)
	{
		gs_grid[gs_playerPosY][gs_playerPosX] = gs_floorTile;
		gs_playerPosX--;
	}
	else if (input == gs_rightKey)
	{
		gs_grid[gs_playerPosY][gs_playerPosX] = gs_floorTile;
		gs_playerPosX++;
	}
	else
		return false;
	gs_grid[gs_playerPosY][gs_playerPosX] = gs_playerTile;
	return true;
}

bool mmorGS::collision(uchar input, uchar tileColl)
{
	ushort tempPosY = gs_playerPosY;
	ushort tempPosX = gs_playerPosX;

	if (input == gs_upKey)
		tempPosY--;
	else if (input == gs_downKey)
		tempPosY++;
	else if (input == gs_leftKey)
		tempPosX--;
	else if (input == gs_rightKey)
		tempPosX++;
	else
		return false;

	if ((gs_grid[tempPosY][tempPosX]) == tileColl)
		return true;
	else
		return false;
}

bool mmorGS::damage()
{
	return false;
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
