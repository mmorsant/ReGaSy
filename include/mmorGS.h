#ifndef mmorGS_h
#define mmorGS_h

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;

class mmorGS
{
private:
	ushort gs_height{10};
	ushort gs_width{10};

	uchar** gs_grid{nullptr};

	ushort gs_playerPosY{1};
	ushort gs_playerPosX{1};
	uint gs_playerLife{5};

	uchar gs_floorTile{176};
	uchar gs_wallTile{219};
	uchar gs_playerTile{64};

	uchar gs_upKey{8};
	uchar gs_downKey{2};
	uchar gs_leftKey{4};
	uchar gs_rightKey{6};

	bool gs_isFirstFrame{true};

public:
	mmorGS() = default;

	bool createWorld(ushort height = 10, ushort width = 10);
	void setTiles(uchar floorTile = 176, uchar wallTile = 219);
	bool spawnPlayer(uchar tile = 64, ushort posY = 1, ushort posX = 1);
	void setPlayerLife(uint amountLife = 5);
	void setKeys(uchar upKey, uchar downKey, uchar leftKey, uchar rightKey);

	bool frame(uchar input, uchar finish);
	void draw();

	bool movePlayer(uchar input);
	bool collision(uchar input, uchar tileColl);
	bool damage();

	~mmorGS();
};

#endif
