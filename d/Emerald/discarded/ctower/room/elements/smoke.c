inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../../ctower.h"
#include <stdproperties.h> 

void
create_ctower_room()
{
  set_short("Smoke room");
 
  set_long( "This room is a clash between the elements "+
      "of air and fire, producing smoke so thick you can barely see.\n" );
 
  add_item(({"smoke"}),  "The smoke is being churned "+
      "rapidly by a very strong wind and is quite warm.\n" );
 
  add_item(({"wall", "ceiling", "floor"}),  "The walls are "+
      "made of a dark crystal that seems to absorb the light.\n" );
 
  add_exit(CTOWER_ROOM_ELEM + "fire1", "west");
  add_exit(CTOWER_ROOM_ELEM + "air1", "east");
  add_exit(CTOWER_ROOM_ELEM + "all", "north");

}
