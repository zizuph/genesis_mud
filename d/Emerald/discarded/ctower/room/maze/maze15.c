#include "../../ctower.h" 

inherit MAZESTD;
 
void
create_maze()
{
  add_maze_exit(CTOWER_ROOM_MAZE + "maze14", "west");
  add_maze_exit(CTOWER_ROOM_MAZE + "maze16", "east");
  add_maze_exit(CTOWER_ROOM_MAZE + "maze19", "south");
}
