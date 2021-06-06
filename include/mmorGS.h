#ifndef mmorGS_h
#define mmorGS_h

#include <vector>

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;

class mmorGS
{
private:
	ushort gs_height{10};
	ushort gs_width{10};
	uchar** gs_grid{nullptr};

	uchar gs_floorTile{176};
	uchar gs_wallTile{219};
	uchar gs_playerTile{64};

	ushort gs_playerPosY{ 1 };
	ushort gs_playerPosX{ 1 };
	int gs_playerLife{ 5 };
	uchar gs_upKey{8};
	uchar gs_downKey{2};
	uchar gs_leftKey{4};
	uchar gs_rightKey{6};

	struct gs_enemy
	{
		ushort id;
		uchar tile;
		uint damage;
		ushort posY;
		ushort posX;
		short moveY;
		short moveX;
	};
	std::vector<gs_enemy> gs_enemies{};

	bool gs_isFirstFrame{true};

public:
	mmorGS() = default;

	bool createWorld(ushort height = 10, ushort width = 10);
	void setTiles(uchar floorTile = 176, uchar wallTile = 219);

	bool frame(uchar input, uchar finish);
	void draw();

	void spawnPlayer(uchar tile = 64, ushort posY = 1, ushort posX = 1);
	void setPlayerLife(int amountLife = 5);
	void setKeys(uchar upKey, uchar downKey, uchar leftKey, uchar rightKey);
	bool movePlayer(uchar input);
	bool playerCollision(uchar input, uchar tileColl);
	bool playerDamage(uchar input);

	void createEnemyBuffer(uint size);
	void createEnemy(uchar tile, uint damage, short moveY, short moveX);
	void spawnEnemy(ushort id, ushort posY, ushort posX);
	void moveEnemies();
	bool enemyCollision(ushort id, int posY, int posX, uchar tileColl);

	~mmorGS();
};

#endif
