inherit "/d/Emerald/ctower/room/ctower_base";
 
#include <stdproperties.h>
#include "../ctower.h"
 
void
create_ctower_room()
{
  set_short("Tower stairs");
 
  set_long( "There is a set of spiral stairs leading up.  "+
      "They are evenly spaced and are almost transparent.  You can see "+
      "that the stairs end one flight up at a landing of dark crystal.\n" );
 
  add_item(({"wall", "floor", "ceiling"}), "The walls are made of a "+
      "milky crystal that is cold to the touch.\n");
 
  add_item("stairs",  "The stairs appear to be quite sturdy "+
      "even though there doesn't seem to be any visible support.\n" );
 
  add_item(({"landing"}),  "The landing is barely visible from "+
      "here.  You will have to climb the stairs to find out more.\n" );
 
  add_exit(CTOWER_ROOM + "trialsd", "up", 0, 3);
  add_exit(CTOWER_ROOM_MAZE + "maze20", "south", 0, 1);

}
