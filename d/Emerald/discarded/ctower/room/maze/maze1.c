#include "../../ctower.h"

inherit MAZESTD;

void create_maze()
{
  add_maze_exit(CTOWER_ROOM_MAZE + "maze2", "west");
  add_maze_exit(CTOWER_ROOM + "stair4", "north");
  add_maze_exit(CTOWER_ROOM_MAZE + "maze3", "east");
}
