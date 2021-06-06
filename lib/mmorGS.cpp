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
			moveEnemies();
			if (!(playerCollision(input, gs_wallTile)))
			{
				if (!(playerDamage(input)))
					movePlayer(input);
				else
				{
					if (gs_playerLife <= 0)
					{
						std::cout << "You are dead" << '\n';
						return false;
					}
					else
						NULL;
				}
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
	
	std::cout << "Life: " << gs_playerLife << '\n';
}


void mmorGS::spawnPlayer(uchar tile, ushort posY, ushort posX)
{
	gs_playerTile = tile;

	gs_playerPosY = posY;
	gs_playerPosX = posX;

	gs_grid[gs_playerPosY][gs_playerPosX] = gs_playerTile;
}
void mmorGS::setPlayerLife(int amountLife)
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
bool mmorGS::playerCollision(uchar input, uchar tileColl)
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
bool mmorGS::playerDamage(uchar input)
{
	for (ushort a{ 0 }; a < gs_enemies.size(); a++)
	{
		if (playerCollision(input, gs_enemies[a].tile))
		{
			gs_playerLife -= gs_enemies[a].damage;
			return true;
		}
	}
	return false;
}

void mmorGS::createEnemyBuffer(uint size)
{
	gs_enemies.reserve(size);
}
void mmorGS::createEnemy(uchar tile, uint damage, short moveY, short moveX)
{
	ushort tempId = (gs_enemies.size());
	gs_enemies.push_back({ tempId, tile, damage, 0, 0, moveY, moveX});
}
void mmorGS::spawnEnemy(ushort id, ushort posY, ushort posX)
{
	gs_enemies[id].posY = posY;
	gs_enemies[id].posX = posX;

	gs_grid[gs_enemies[id].posY][gs_enemies[id].posX] = gs_enemies[id].tile;
}
void mmorGS::moveEnemies()
{
	for (ushort a{0}; a < gs_enemies.size(); a++)
	{
		if (!(enemyCollision(a, gs_enemies[a].moveY, gs_enemies[a].moveX, gs_wallTile)))
		{
			gs_grid[gs_enemies[a].posY][gs_enemies[a].posX] = gs_floorTile;

			gs_enemies[a].posY = (gs_enemies[a].posY) + (gs_enemies[a].moveY);
			gs_enemies[a].posX = (gs_enemies[a].posX) + (gs_enemies[a].moveX);

			gs_grid[gs_enemies[a].posY][gs_enemies[a].posX] = gs_enemies[a].tile;
		}
		else
		{
			gs_enemies[a].moveY = -(gs_enemies[a].moveY);
			gs_enemies[a].moveX = -(gs_enemies[a].moveX);
		}
	}
}
bool mmorGS::enemyCollision(ushort id, int posY, int posX, uchar tileColl)
{
	ushort tempPosY = gs_enemies[id].posY + (posY);
	ushort tempPosX = gs_enemies[id].posX + (posX);

	if ((gs_grid[tempPosY][tempPosX]) == tileColl)
		return true;
	else
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
