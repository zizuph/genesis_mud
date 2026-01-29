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
  set_long("You are standing in a corridor leading east and west. " +
	   "To the east you can see the end of the tunnel, and to " +
	   "north you can see a storeroom." +
	   " \n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "Traproom","east",0,1);
  add_exit(THIS_DIR + "cave48","west",0,1,);
  add_exit(THIS_DIR + "storeroom","north",0,1);
}
