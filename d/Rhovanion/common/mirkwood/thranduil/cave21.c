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
  set_long("This looks like the place where the King keeps his parties" +
	    ". You see a corridor going southwest to the throneroom, and " +
            "the halls continue to the east."
	    + " \n");

  add_item("party","There is a party going on all the time here. \n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave22","east",0,1);
  add_exit(THIS_DIR + "throneroom","southwest",0,1);
}
