#include "../../ctower.h"

inherit MAZESTD;
 
void
create_maze()
{
  add_maze_exit(CTOWER_ROOM_MAZE + "maze1", "east");
  add_maze_exit(CTOWER_ROOM_MAZE + "maze5", "south");
}
