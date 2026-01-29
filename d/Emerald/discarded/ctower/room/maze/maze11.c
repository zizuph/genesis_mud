#include "../../ctower.h" 

inherit MAZESTD;
 
void
create_maze()
{
  add_maze_exit(CTOWER_ROOM_MAZE + "maze10", "west");
  add_maze_exit(CTOWER_ROOM_MAZE + "maze16", "south");
}
