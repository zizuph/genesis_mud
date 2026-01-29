#include "defs.h"

inherit STDGATEROOM;


create_gateroom() {
  set_short("Western gate of Bree");
  set_long("@@my_long");
  set_other_room(STAND_DIR + "townr1");
  set_direction("east");
  add_exit(STAND_DIR + "cross", "west");
}

my_long() {
  string str;

  if (gatestate) str = "The gates are open. ";
  else str = "The gates are closed to keep villains out. ";
  return break_string("You are standing in front of the western gates of "+
         "the little village Bree. " + str + "The village lies east, and "+
         "the eastroad is to the west.\n", 70);
}
