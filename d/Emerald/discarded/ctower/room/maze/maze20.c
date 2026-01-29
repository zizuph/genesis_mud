#include "../../ctower.h"

inherit MAZESTD;

void create_maze()
{
  add_maze_exit(CTOWER_ROOM + "mazesu", "south");
  add_maze_exit(CTOWER_ROOM_MAZE + "maze19", "west");
  add_maze_exit(CTOWER_ROOM_MAZE + "maze21", "east");
}
