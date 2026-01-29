inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../../ctower.h"
#include <stdproperties.h>
 
void
create_ctower_room()
{
  set_short("Tower hall");
 
  set_long("The walls of this hallway give off a soft "+
      "glow\nthat gives everything an unreal appearance.\n");
 
  add_item(({"wall", "floor", "ceiling"}), "The walls are made of a "+
      "milky crystal that is cold to the touch.\n");
 
  add_exit("hall6", "west");
  add_exit("study1", "north");
  add_exit("study2", "east");
  add_exit(CTOWER_ROOM_LIBRARY + "blib1", "south");

}
