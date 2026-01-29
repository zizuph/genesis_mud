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
  set_long(" You stand in a bend in the corridor, which is leading " +
	   " to the west and southeast, to the west you see a split in " +
	   " it." +
	   " \n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave33","west",0,1);
  add_exit(THIS_DIR + "cave38","southeast",0,1,);
}
