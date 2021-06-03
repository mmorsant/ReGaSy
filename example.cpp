#include <iostream>

#include <mmorGS.h>

int main ()
{
  mmorGS game;
  game.createWorld(10, 20);
  game.setTiles(176);
  
  ushort key {0};
  
  while (game.frame(key, 5))
  {
    key = 0;
    std::cin >> key;
  }
  
  return 0;
}
