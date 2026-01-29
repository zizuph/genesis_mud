/*
ROOM: Fire Brigade bedroom of the firemen
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
  
  set_short("This is the common bedroom of the firemen");
  set_long(
    "You are on the second floor of the fire brigade, in the bedroom of "+
    "all the firemen. There are some bunkbeds standing against the wall "+
    "and it seems that they are filled by firemen, judging from the snores. "+
      "No wonder these guys always arrive when the fire has already burned "+
    "itself out!\n"
  );
  
  add_prop(ROOM_NO_TIME_DESC, 1);
    
  add_exit(CENTRAL(plaza/fb_rm21), "west", 0, 0, 0);

  add_item(({"beds", "bunkbeds"}),  
    "You come to the conclusion that any kind of bed should be made "+
    "illegal in a fire brigade. But then, maybe it already is.\n"
  );
}
