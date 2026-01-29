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
  set_long("The tunnel ends here, in the floor you see a trapdoor, " +
	   "You wonder what it is used for. The tunnel leaves back west. "
	   + " \n");
  
  add_item(({"door","trapdoor"}),
             "The trapdoor seems to be magically locked.\n");
  
  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave49","west",0,1);
}
