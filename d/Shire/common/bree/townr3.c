#include "defs.h"

inherit STDGATEROOM;

create_gateroom() {
  set_short("Road in Bree");
  set_long("@@my_long");
  set_other_room(STAND_DIR + "sgate");
  set_direction("south");
  add_exit(STAND_DIR + "townrm", "north");
}

my_long() {
  string str;

  if (gatestate) str = "The gates are currently open";
  else str = "The gates are currently closed";
  return break_string("You are standing inside the southern gates of Bree. "+
         "The village is a cosy place, and an air of peace and tranquility "+
         "can be smelled. At least you're a bit protected here. "+
         "You feel good about that. To the north lies a crossroad where "+
         "three roads meet, to the south the road leaves the safety of "+
         "Bree through the southern gates. " + str + ".\n", 70);
}
