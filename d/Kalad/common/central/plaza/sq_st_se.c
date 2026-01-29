/*
ROOM: South Plaza Street (east)
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

  set_short("The east part of South Plaza Street");
  set_long(
    "This is the east part of South Plaza Street. This wide, well-paved "+
    "east-west road leads to the Guild Circle on the east, and the Town "+
    "Square on the west. "
  );

  add_exit(CENTRAL(circle/s6), "east", 0);
  add_exit(CENTRAL(plaza/sq_south), "west", 0);
}
