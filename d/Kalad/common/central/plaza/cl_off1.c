/*
ROOM: Council of Lords Administration office
BY:   Sebster
DATE: Aug 28, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

void
create_room()
{
  ::create_room();
  hear_bell = 2;

  add_prop(ROOM_I_INSIDE, 1);
  
  set_short("The Council of Lords Administration office");
  set_long(
    "This is the Council of Lords Administration office. Between all the "+
    "ornaments and other decorations some overly wealthy lord has "+
    "installed here, there is relatively little of interest. There is "+
    "a big wooden desk where the Adminstrator usually sits. \n"
  );

  add_prop(ROOM_NO_TIME_DESC, 1);

   add_exit(CENTRAL(plaza/cl_hall1), "west", 0, -1, -1);

   add_item("desk","A beautiful oak writing desk.\n");
  
  add_item(({"decorations", "ornaments"}),
    "Obviously the Lords have too much money on their hands; these "+
    "ornaments are UGLY!\n"
  );
}
