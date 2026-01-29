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
  set_long(" You stand in a split in the corridor, you see exits " +
	   "to the east, west and southwest." +
	   " \n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave48","east",0,1);
  add_exit(THIS_DIR + "cave46","west",0,1,);
  add_exit(THIS_DIR + "cave43","southwest",0,1);
}
