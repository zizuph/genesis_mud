inherit "/d/Rhovanion/lib/caves.c";

#include "def.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h";

create_cave()
{
  set_rock_type("soluble limestone");
  set_cave_name("Thranduil's Caverns");
  set_region("northern");
  set_cave("Mirkwood");
  set_cave_type(1);
  set_long(" You stand in a corridor leading east and west, " +
	   "north are some well-worn steps to a large cavern.  \n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave32","east",0,1);
  add_exit(THIS_DIR + "cave30","west",0,1,);
  add_exit(THIS_DIR + "adv_guild","north",0,1);
}
