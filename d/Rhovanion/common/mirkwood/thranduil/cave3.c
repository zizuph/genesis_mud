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

  set_long("The corridor continues to the southeast and northwest, to the "
	   + "north you see Thranduil's Throneroom. \n");
  add_item("throneroom","You can't see it well from here.\n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave4","northwest",0,1);
  add_exit(THIS_DIR + "cave2","southeast",0,1);
  add_exit(THIS_DIR + "throneroom","north",0,1);
}
