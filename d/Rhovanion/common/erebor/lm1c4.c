inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

create_cave()
{
  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(5);
  set_long("Suddenly you realize that you have entered "
	 + "a room for the guards of Lonely Mountain. "
         + ""
         + ""
         + "In the centre of the room is a table with "
         + "four adjoining chairs.");

  add_exit(ERE_DIR + "lm1c2","west",0,1);
}
