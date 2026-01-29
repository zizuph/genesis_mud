#include "../../ctower.h" 

inherit MAZESTD;
 
void
create_maze()
{
  add_maze_exit(CTOWER_ROOM_MAZE + "maze6", "west");
  add_maze_exit(CTOWER_ROOM_MAZE + "maze8", "east");
}
