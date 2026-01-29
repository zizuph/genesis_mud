/*
ROOM: Fire Brigade entrance
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
  
  set_short("This is the entrance of the Fire Brigade");
  set_long(
    "You are on the first floor of the infamous Fire Brigade. This being a "+
    "very plain hall, you see nothing interest other than the sliding pole "+
    "which arrives here from the second floor, used by the firemen in "+
    "emergencies. You wonder where all the firemen are, no sounds breaking "+
    "the silence other than an occasional faint snore.\n"
  );
  
  add_prop(ROOM_NO_TIME_DESC, 1);
  
  add_exit(CENTRAL(plaza/fb_rm12), "north", 0, 0, 0);
  add_exit(CENTRAL(plaza/sq_east), "out", 0, 0, 0);

  add_item("pole",
    "The pole, which extends to the second floor, looks like it's extremely "+
    "slippery.\n"
  );
}

void
init()
{
  ::init();
  add_action("do_climb", "climb");
}

int
do_climb(string str)
{
  if (str != "pole")
  {
    notify_fail("Climb what?\n");
    return 0;
  }
  write(
    "You try to climb the pole but fail, because it's much too slippery. "+
    "Instead you fall flat on you face in the dirt.\n"
  );
  say(QCTNAME(this_player()) + " tries to climb the pole but falls flat "+
    "on his face in the dirt.\n");
  return 1;
}
