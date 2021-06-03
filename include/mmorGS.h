#ifndef mmorGS_h
#define mmorGS_h

typedef unsigned short ushort;
typedef unsigned char uchar;

class mmorGS
{
public:
	mmorGS() :	gs_height{ 10 }, 
			gs_width{ 10 },
			gs_grid{ nullptr },
			gs_floorTile{ 176 },
			gs_wallTile{ 219 },
			gs_isFirstFrame{ true } {}

	bool createWorld(ushort height = 10, ushort width = 10);
	bool setTiles(uchar floorTile = 176);
	bool frame(ushort input, ushort finish);
	void draw();

	~mmorGS();

private:
  ushort gs_height;
  ushort gs_width;

  char** gs_grid;

  uchar gs_floorTile;
  uchar gs_wallTile;

  bool gs_isFirstFrame;
};

#endif
