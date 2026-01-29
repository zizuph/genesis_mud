#include "../../ctower.h"

inherit MAZESTD;
 
void
ctower_reset()
{
    if (present("ctower_wand"))
    {
        return;
    }
  
    clone_object(CTOWER_OBJ + "wand")->move(this_object(), 1);
}
 
void
create_maze()
{
    add_maze_exit(CTOWER_ROOM_MAZE + "maze9", "east");
    ctower_reset();
}
