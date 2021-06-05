#include <iostream>

#include <mmorGS.h>

int main()
{
	mmorGS game;
	game.createWorld(10, 20);
	game.setTiles(' ', 219);
	game.spawnPlayer( 64, 5, 5);
	game.setPlayerLife(10);
	game.setKeys( 'w', 's', 'a', 'd');

	uchar key{0};

	while (game.frame(key, '5'))
	{
		key = 0;
		std::cin >> key;
	}

	return 0;
}
