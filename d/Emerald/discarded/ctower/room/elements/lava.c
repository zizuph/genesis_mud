inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../../ctower.h"
#include <stdproperties.h> 

void
create_ctower_room()
{
  set_short("Lava room");
 
  set_long( "This room is a clash between the elements of "+
      "fire and earth, producing a thick viscous lava.\n" );
 
  add_item(({"floor", "lava"}),  "The lava is churning "+
      "slowly and you can see the waves of heat radiating from the "+
      "floor.\n" );
 
  add_item(({"wall", "ceiling"}),  "The walls are "+
      "made of a dark crystal that seems to absorb the light.\n" );
 
  add_exit(CTOWER_ROOM_ELEM + "fire1", "south");
  add_exit(CTOWER_ROOM_ELEM + "all", "east");
  add_exit(CTOWER_ROOM_ELEM + "earth1", "north");

}
