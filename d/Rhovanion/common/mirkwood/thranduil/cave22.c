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
  set_cave_type(2);
  set_long(" It looks like the King make parties in these halls, the caves "
	   + "continues to the east and west, to the south there is a "
	   + "corridor."
	   + " \n");

  add_item("party","There is a party going on all the time here. \n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave23","east",0,1);
  add_exit(THIS_DIR + "cave25","south",0,1);
  add_exit(THIS_DIR + "cave21","west",0,1);
}
