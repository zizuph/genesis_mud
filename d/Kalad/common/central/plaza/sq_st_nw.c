/*
ROOM: North Plaza Street (west)
BY:   Sebster
DATE: Aug 27, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

void
create_room()
{
  ::create_room();
  hear_bell = 3;

  set_short("The west part of North Plaza Street");
  set_long(
    "This is the west part of North Plaza Street. This wide, well-paved "+
    "east-west road leads to the Guild Circle on the west, and the Town "+
    "Square on the east. "
  );

  add_exit(CENTRAL(plaza/sq_north), "east", 0);
   add_exit(CENTRAL(circle/s13), "west", 0);
}
