#include "../../ctower.h"

inherit MAZESTD;

void create_maze()
{
  add_maze_exit("maze2", "west");
  add_maze_exit(CTOWER_ROOM_ENTRY + "stair3", "north");
  add_maze_exit("maze3", "east");
}
