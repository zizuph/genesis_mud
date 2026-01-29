inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../ctower.h"
#include <stdproperties.h> 

int block();

void
create_ctower_room()
{
  set_short("Tower entry");
 
  set_long( "The archway seems to absorb all light.  "+
      "You can barely see anything.\n" );
 
  add_exit(CTOWER_ROOM + "hall1", "north");
  add_exit(CTOWER_ROOM + "pointday", "out");
  add_exit(CTOWER_ROOM + "entry", "south");
  add_exit(CTOWER_ROOM + "entry", "east");
  add_exit(CTOWER_ROOM + "entry", "west");
  add_exit("none", "northeast", block);
  add_exit("none", "northwest", block);
  add_exit("none", "southeast", block);
  add_exit("none", "southwest", block);
 
  set_noshow_obvious(1);
  add_prop(ROOM_I_LIGHT, -100);
}
 
int
block()
{
    write("You bump your head into a wall.\n");
    return 1;
}
