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
  set_cave_type(5);
  set_long("You realize that you must have entered "
	 + "the office of the Captain of the Front Gate. "
         + "Maybe you had better get out of here while you "
         + "still can. A big impressive desk dominates the "
         + "room.");

  door = clone_object(ERE_DIR + "door_lm1c3");
  door->move(TO);

  add_item("desk", "The desk is impetously organized. Not a "+
           "single thing is misplaced. Neat, is the word!\n");
}
