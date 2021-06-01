#include <iostream>
#include <cstdlib>

namespace GRID
{
	constexpr int width{ 20 };
	constexpr int height{ 10 };

	const int extremeXplus{ (width - 2) };
	const int extremeXminus{ (width - (width - 1)) };
	const int extremeYplus{ (height - 2) };
	const int extremeYminus{ (height - (height - 1)) };
}

namespace PLAYER
{
	int positionX{ 1 };
	int positionY{ 1 };
}

namespace TILE
{
	constexpr char player = 64;
	constexpr char floor = 176;
	constexpr char wall = 219;
}

class GameSystem
{
private:
	char** m_grid;
	bool m_firstRun;

public:
	GameSystem() : m_firstRun{true}					//allocate memory and create actors
	{
		m_grid = new char*[GRID::height];			//rounds
		for (int a{ 0 }; a < (GRID::height); a++)		//columns
		{
			m_grid[a] = new char [GRID::width];
		}
	}

	void init()							//floor, wall and player tiles set
	{
		for (int a{ 0 }; a < (GRID::height); a++)		//rounds
		{
			for (int b{ 0 }; b < (GRID::width); b++)	//columns
			{
				m_grid[a][b] = TILE::floor;
			}
		}

		m_grid[PLAYER::positionY][PLAYER::positionX] = TILE::player;

		//make default walls
		for (int a{0}; a < (GRID::width); a++)			//superior
		{
			m_grid[0][a] = TILE::wall;
		}
		for (int a{0}; a < (GRID::height); a++)			//left
		{
			m_grid[a][0] = TILE::wall;
		}
		for (int a{0}; a < (GRID::height); a++)			//right
		{
			m_grid[a][GRID::width - 1] = TILE::wall;
		}
		for (int a{0}; a < (GRID::width); a++)			//inferior
		{
			m_grid[GRID::height - 1][a] = TILE::wall;
		}
	}

	bool state(int& input)						//player movement and draw
	{
		// > to second state put floor on the player was
		if (m_firstRun == true)
		{
			m_firstRun = false;
		}
		else 
		{
			m_grid[PLAYER::positionY][PLAYER::positionX] = TILE::floor;
		}
		
		//movement system
		switch (input)
		{
		case 4:
			//move left
			if (PLAYER::positionX == GRID::extremeXminus)
			{
				m_grid[PLAYER::positionY][PLAYER::positionX] = TILE::player;
			}
			else
			{
				PLAYER::positionX--;
				m_grid[PLAYER::positionY][PLAYER::positionX] = TILE::player;
			}
			break;
		case 6:
			//move right
			if(PLAYER::positionX == GRID::extremeXplus)
			{
				m_grid[PLAYER::positionY][PLAYER::positionX] = TILE::player;
			}
			else
			{
				PLAYER::positionX++;
				m_grid[PLAYER::positionY][PLAYER::positionX] = TILE::player;
			}
			break;
		case 8:
			//move up
			if(PLAYER::positionY == GRID::extremeYminus)
			{
				m_grid[PLAYER::positionY][PLAYER::positionX] = TILE::player;
			}
			else
			{
				PLAYER::positionY--;
				m_grid[PLAYER::positionY][PLAYER::positionX] = TILE::player;
			}
			break;
		case 2:
			//move down
			if (PLAYER::positionY == GRID::extremeYplus)
			{
				m_grid[PLAYER::positionY][PLAYER::positionX] = TILE::player;
			}
			else
			{
				PLAYER::positionY++;
				m_grid[PLAYER::positionY][PLAYER::positionX] = TILE::player;
			}
			break;
		case 5:
			return false;
		}
		
		//console output
		draw();

		return true;
	}

	void draw()							//console out the grid
	{
		for (int a{ 0 }; a < (GRID::height); a++)
		{
			for (int b{ 0 }; b < (GRID::width); b++)
			{
				std::cout << m_grid[a][b];
			}
			std::cout << '\n';
		}
	}

	~GameSystem()							//deallocate memory
	{
		for (int a{ 0 }; a < (GRID::height); a++)
		{
			delete[] m_grid[a];
		}
		delete m_grid;
		m_grid = nullptr;
	}
};

int main()
{
	GameSystem run;
	run.init();

	int key{ 0 };

	while (run.state(key))
	{
		key = 0;
		std::cin >> key;
		system("CLS");
	}

	return 0;
}
