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
  set_long("There is a staircase in the middle of the room leading up, "
	   + "and a corridor leads east.\n");
  add_item(({"staircase","stair"}),
             "You may be able to use it and get to upper level.\n");
  
  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave29","east",0,1);
  add_exit(THIS_DIR + "stair1","up",0,1);
}
