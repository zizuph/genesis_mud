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
  set_long(" The corridor continues east and southwest. "
	   + " \n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave6","east",0,1);
  add_exit(THIS_DIR + "cave8","southwest",0,1);
}
