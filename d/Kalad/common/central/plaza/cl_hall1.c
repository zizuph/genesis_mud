/*
ROOM: Council of Lords entrance hall
BY:   Sebster
DATE: Aug 27, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

void
create_room()
{
  ::create_room();
  hear_bell = 2;

  add_prop(ROOM_I_INSIDE, 1);
  
  set_short("The hallway of the Council of Lords building");
  set_long(
    "The Council of Lords building consists of a long hallway with several "+
    "offices, and a debate chamber at the end. There are nice decorations "+
    "everywhere, and the inside walls are not as charred as the outside "+
    "walls. Somebody must have cleaned them. "
  );
  set_time_desc(
    "Many distinguished Lords are walking up and down the corridor.\n",
    "Several Lords are snooping around, probably searching file "+
    "cabinets in the offices.\n"
  );

   add_exit(CENTRAL(plaza/cl_hall2), "north", 0, -1,-1);
   add_exit(CENTRAL(plaza/cl_off1), "east", 0, -1, -1);
   add_exit(CENTRAL(plaza/sq_north), "out", 0, -1, -1);

  add_item("offices",
    "There is an office to the west with a sign on the door.\n"
  );
  
  add_item(({"office", "sign"}),
    "The office to the east has a sign onthe door reading 'Council "+
    "of Lords Administration.'\n"
  );
}
