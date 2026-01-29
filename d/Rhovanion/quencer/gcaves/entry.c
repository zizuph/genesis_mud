#include "stdroom.h"

create_room()
{
  set_short("Inside the cave");
  set_long(BS("You stand inside a large, damp cave.  The room is almost "
    + "featureless, but there is a crack in the east wall which draws your "
    + "attention.  To the west, the cave opens into a rocky valley.\n"));
   
  add_item("crack", BS("This is a fairly good sized crack which seems to "
    + "have opened in the cave wall.  A soft breeze blows from the crack, "
    + "bringing the smell of damp earth and something else you can't quite "
    + "identify.\n"));
  add_prop(ROOM_I_LIGHT, 1);
  add_prop(ROOM_I_INSIDE, 1);
   
  add_exit(RPATH + "cave", "west");
  add_exit(RPATH + "tunnel00", "crack", "@@descend");
}


int descend()
{
  write("You squeeze through the crack.\n");

  return 0;
}
