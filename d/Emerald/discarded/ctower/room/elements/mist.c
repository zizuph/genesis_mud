inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../../ctower.h"
#include <stdproperties.h>
 
void
create_ctower_room()
{
  set_short("Mist room");
 
  set_long( "This room is a clash between the elements of "+
      "air and water, producing a thick mist so thick you can barely "+
      "see.\n" );
 
  add_item(({"mist"}),  "The mist is being churned "+
      "rapidly by a very strong wind and is wet and cold.\n" );
 
  add_item(({"wall", "ceiling", "floor"}),  "The walls are "+
      "made of a dark crystal that seems to absorb the light.\n" );
 
  add_exit(CTOWER_ROOM_ELEM + "air1", "south");
  add_exit(CTOWER_ROOM_ELEM + "water1", "north");
  add_exit(CTOWER_ROOM_ELEM + "all", "west");

}
