#include "defs.h"

inherit STDGATEROOM;

create_gateroom() {
  set_short("Southern gate of Bree");
  set_long("@@my_long");
  set_other_room(STAND_DIR + "townr3");
  set_direction("north");
  add_exit(STAND_PARENT + "/greenway/gw1", "south", 0);
}

my_long() {
  string str;

  if (gatestate) str = "The gates are open. ";
  else str = "The gates are closed to keep villains out. ";
  return break_string("You are standing in front of the southern gates of "+
         "the little village Bree. " + str + "The village lies north, and "+
         "the long Greenroad leads south towards Rohan and Gondor.\n", 70);
}

