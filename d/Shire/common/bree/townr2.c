#include "defs.h"

inherit STDGATEROOM;

create_gateroom() {
  set_short("By the South-Gate");
  set_long("@@my_long");
  set_other_room(STAND_DIR + "egate");
  set_direction("east");
  add_exit(STAND_DIR + "townrm", "northwest");
}

my_long() {
  string str;

  if (gatestate) str = "The South-Gate is currently open";
  else str = "The South-Gate is currently closed";
  return break_string(
	 "You are standing by the Gatekeeper's lodge by the South-Gate. "+
	 "To the north you see Bree-hill, where in the lower parts men's "+
	 "houses are, and further up a lot of hobbit holes are. The Great "+
	 "East Road enters here through the South-gate and continues northwest "+
	 "along the hill. "+str+".\n", 70);
}
