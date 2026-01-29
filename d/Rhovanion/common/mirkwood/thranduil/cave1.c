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
  set_long("You are standing in the entrance hall of "
	   + "Thranduil's Caverns. To the south you "
	   + "see the great gate and to the north "
	   + "there is a corridor.");
  add_item("gate",BS("This is a sturdy gate. A magical aura " +
                     "seems to penetrate it's surface. It would " +
                     "appear impossible to break it down or " +
                     "open it without the explicit permission of " +
                     "Thranduil himself, King of the Caverns.\n"));
  add_item("corridor","It leads deep into the caves.\n");
  
  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave2","north",0,1);
  add_exit(MIRK_DIR+"mirk-19-8-T", "south", 0, 1);

}
