#include "../../ctower.h" 

inherit MAZESTD;
 
void
create_maze()
{
  add_maze_exit(CTOWER_ROOM_MAZE + "maze15", "east");
  add_maze_exit(CTOWER_ROOM_MAZE + "maze9", "north");
}
