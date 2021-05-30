#include <iostream>
#include <cstdlib>

namespace ID
{
	const int width{ 20 };
	const int height{ 10 };

	const char player = 64;
	const char floor = 176;
	const char wall = 219;

	int positionX{ 1 };
	int positionY{ 1 };

	const int extremeXplus{ (width - 2) };
	const int extremeXminus{ (width - (width - 1)) };
	const int extremeYplus{ (height - 2) };
	const int extremeYminus{ (height - (height -1)) };
}

class GameSystem
{
private:
	char** m_grid;
	bool m_firstRun;

public:
	GameSystem() : m_firstRun{true}
	{
		m_grid = new char*[ID::height];			//rounds
		for (int a{ 0 }; a < (ID::height); a++)	//columns
		{
			m_grid[a] = new char [ID::width];
		}
	}

	void init()
	{
		for (int a{ 0 }; a < (ID::height); a++)			//rounds
		{
			for (int b{ 0 }; b < (ID::width); b++)		//columns
			{
				m_grid[a][b] = ID::floor;
			}
		}

		m_grid[ID::positionY][ID::positionX] = ID::player;

		//make default walls
		for (int a{0}; a < (ID::width); a++)		//superior
		{
			m_grid[0][a] = ID::wall;
		}
		for (int a{0}; a < (ID::height); a++)		//left
		{
			m_grid[a][0] = ID::wall;
		}
		for (int a{0}; a < (ID::height); a++)		//right
		{
			m_grid[a][ID::width - 1] = ID::wall;
		}
		for (int a{0}; a < (ID::width); a++)		//inferior
		{
			m_grid[ID::height - 1][a] = ID::wall;
		}
	}

	bool state(int& input)
	{
		// > to second state put floor on the player was
		if (m_firstRun == true)
		{
			m_firstRun = false;
		}
		else 
		{
			m_grid[ID::positionY][ID::positionX] = ID::floor;
		}
		
		//movement system
		switch (input)
		{
		case 4:
			//move left
			if (ID::positionX == ID::extremeXminus)
			{
				m_grid[ID::positionY][ID::positionX] = ID::player;
			}
			else
			{
				ID::positionX--;
				m_grid[ID::positionY][ID::positionX] = ID::player;
			}
			break;
		case 6:
			//move right
			if(ID::positionX == ID::extremeXplus)
			{
				m_grid[ID::positionY][ID::positionX] = ID::player;
			}
			else
			{
				ID::positionX++;
				m_grid[ID::positionY][ID::positionX] = ID::player;
			}
			break;
		case 8:
			//move up
			if(ID::positionY == ID::extremeYminus)
			{
				m_grid[ID::positionY][ID::positionX] = ID::player;
			}
			else
			{
				ID::positionY--;
				m_grid[ID::positionY][ID::positionX] = ID::player;
			}
			break;
		case 2:
			//move down
			if (ID::positionY == ID::extremeYplus)
			{
				m_grid[ID::positionY][ID::positionX] = ID::player;
			}
			else
			{
				ID::positionY++;
				m_grid[ID::positionY][ID::positionX] = ID::player;
			}
			break;
		case 5:
			return false;
		}
		
		//console output
		draw();

		return true;
	}

	void draw()
	{
		for (int a{ 0 }; a < (ID::height); a++)
		{
			for (int b{ 0 }; b < (ID::width); b++)
			{
				std::cout << m_grid[a][b];
			}
			std::cout << '\n';
		}
	}

	~GameSystem()
	{
		for (int a{ 0 }; a < (ID::height); a++)
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
