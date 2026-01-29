#include "../../ctower.h" 

inherit MAZESTD;
 
void
create_maze()
{
  add_maze_exit(CTOWER_ROOM_MAZE + "maze4", "west");
  add_maze_exit(CTOWER_ROOM_MAZE + "maze6", "east");
  add_maze_exit(CTOWER_ROOM_MAZE + "maze2", "north");
  add_maze_exit(CTOWER_ROOM_MAZE + "maze10", "south");
}
