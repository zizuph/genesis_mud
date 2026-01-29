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
  set_long(" You stand in a split in the tunnel, you see forks leading, " +
	   "northwest, southwest and east. " +
	   " \n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave36","southwest",0,1);
  add_exit(THIS_DIR + "cave32","northwest",0,1,);
  add_exit(THIS_DIR + "cave37","east",0,1);
}
