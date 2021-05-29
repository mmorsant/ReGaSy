#include <iostream>
#include <cstdlib>

namespace ID
{
	enum id
	{
		player = 64,
		floor = 176,
		wall = 219
	};

	int positionX{0};
	int positionY{0};
}

class Rpg
{
private:
	int** ptr;
	bool inGame;

public:
	Rpg() : inGame{true}
	{
		ptr = new int*[10];	                //rounds
		for (int a{ 0 }; a < 10; a++)		//columns
		{
			ptr[a] = new int [10];
		}
	}

	void init()
	{
		for (int a{ 0 }; a < 10; a++)
		{
			for (int b{ 0 }; b < 10; b++)
			{
				ptr[a][b] = ID::floor;
			}
		}

		ptr[ID::positionY][ID::positionX] = ID::player;
	}

	bool state(int& input)
	{
		if (inGame == true)
		{
			inGame = false;
		}
		else 
		{
			ptr[ID::positionY][ID::positionX] = ID::floor;
		}

		switch (input)
		{
		case 4:
			//move left
			if (ID::positionX == 0) 
			{
				ptr[ID::positionY][ID::positionX] = ID::player;
			}
			else
			{
				ID::positionX--;
				ptr[ID::positionY][ID::positionX] = ID::player;
			}
			break;
		case 6:
			//move right
			if(ID::positionX == 9)
			{
				ptr[ID::positionY][ID::positionX] = ID::player;
			}
			else
			{
				ID::positionX++;
				ptr[ID::positionY][ID::positionX] = ID::player;
			}
			break;
		case 8:
			//move up
			if(ID::positionY == 0)
			{
				ptr[ID::positionY][ID::positionX] = ID::player;
			}
			else
			{
				ID::positionY--;
				ptr[ID::positionY][ID::positionX] = ID::player;
			}
			break;
		case 2:
			//move down
			if (ID::positionY == 9)
			{
				ptr[ID::positionY][ID::positionX] = ID::player;
			}
			else
			{
				ID::positionY++;
				ptr[ID::positionY][ID::positionX] = ID::player;
			}
			break;
		case 5:
			return false;
		}

		frame();

		return true;
	}

	void frame()
	{
		for (int a{ 0 }; a < 10; a++)
		{
			for (int b{ 0 }; b < 10; b++)
			{
				std::cout << static_cast<char>(ptr[a][b]);
			}
			std::cout << '\n';
		}
	}

	~Rpg()
	{
		for (int a{ 0 }; a < 10; a++)
		{
			delete[] ptr[a];
		}
		delete ptr;
		ptr = nullptr;
	}
};

int main()
{
	Rpg game;
	game.init();

	int move{ 0 };

	while (game.state(move))
	{
		move = 0;
		std::cin >> move;
		system("CLS");
	}

	return 0;
}
