inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

create_cave()
{
  object door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(2);
  set_long("You are standing in the main entrance hall of "
	 + "the Lonely mountain. Along the west wall runs "
         + "the River Running in a deep canal. To the south "
         + "towers the steel reinforced Front Gate and to "
         + "the north you see a corridor.");

  door = clone_object(ERE_DIR + "door_lm1c1");
  door->move(TO);
  
  add_exit(ERE_DIR + "lm1c2","north",0,1);
}
