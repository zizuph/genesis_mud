/*
ROOM: Fire Brigade first floor staircase
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
  
  set_short("This is the staircase of the Fire Brigade");
  set_long(
    "You are on the first floor of the fire brigade. You see an old wooden "+
    "staircase leading up to the second floor. There is still no sign of "+
    "any activity, but the snoring is getting louder.\n"
  );
  
  add_prop(ROOM_NO_TIME_DESC, 1);
  
  add_exit(CENTRAL(plaza/fb_rm11), "south", 0, 0, 0);
  add_exit(CENTRAL(plaza/fb_rm21), "up", 0, 0, 0);

  add_item("stairs", 
    "The old, creaking wooden stairs look like they've been used a lot."
  );
}
