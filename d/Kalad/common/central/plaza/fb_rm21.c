/*
ROOM: Fire Brigade second floor staircase
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
    "You are on the second floor of the fire brigade. You see an old wooden "+
    "staircase leading down to the first floor. To the south you see the "+
    "emergency sliding pole, and to the east you hear a very interesting "+
    "musical concert composed of several different kinds of snoring. "
  );
  set_time_desc("Who would be sleeping at this hour?\n", "\n");
           
  add_exit(CENTRAL(plaza/fb_rm22), "south", 0, 0, 0);
  add_exit(CENTRAL(plaza/fb_bedrm), "east", 0, 0, 0);
  add_exit(CENTRAL(plaza/fb_rm12), "down", 0, 0, 0);

  add_item("stairs", 
    "The old, creaking wooden stairs look like they've been used a lot."
  );
}
