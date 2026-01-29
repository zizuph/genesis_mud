#include "../../ctower.h" 

inherit MAZESTD;
 
void
create_maze()
{
  add_maze_exit(CTOWER_ROOM_MAZE + "maze18", "east");
  add_maze_exit(CTOWER_ROOM_MAZE + "maze12", "north");
  add_maze_exit(CTOWER_ROOM_MAZE + "maze21", "south");
}
