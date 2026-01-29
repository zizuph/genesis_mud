#include "../../ctower.h"

inherit MAZESTD;

void create_maze()
{
  add_maze_exit("maze_out", "south");
  add_maze_exit("maze19", "west");
  add_maze_exit("maze21", "east");
}
