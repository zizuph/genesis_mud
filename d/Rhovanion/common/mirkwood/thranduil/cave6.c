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
  set_long("The corridor continues to the west and east, to "
	   + "the south you see a shop.");
  add_item("shop","You might be able sell or buy some things there.\n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave5","east",0,1);
  add_exit(THIS_DIR + "cave7","west",0,1);
  add_exit(THIS_DIR + "shop","south",0,1);
}
