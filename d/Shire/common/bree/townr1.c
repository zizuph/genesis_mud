#include "defs.h"

inherit STDGATEROOM;

create_gateroom() {
  set_short("Road in Bree");
  set_long("@@my_long");
  set_other_room(STAND_DIR + "wgate");
  set_direction("west");
  add_exit(STAND_DIR + "crossing", "east");
}

my_long() {
  string str;

  if (gatestate) str = "The gates are currently open";
  else str = "The gates are currently closed";
  return break_string("You are in the western part of Bree. To the east is "+
         "a crossroad and to the west are the western gates of this little "+
	 "village. " + str + ".\n", 70);
}
