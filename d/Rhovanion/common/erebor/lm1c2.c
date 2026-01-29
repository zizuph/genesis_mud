inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

create_cave()
{
  object west_door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("Here you can see a door in the west wall. It's "
         + "accessible via a small bridge crossing the River "
         + "Running. To the east you face an opening with a "
         + "sign over it. Further south you see the Front gate "
         + "and to the north the corridor continues.");

  west_door = clone_object(ERE_DIR + "door_lm1c2");
  west_door->move(TO);

  add_item("sign", "It reads:\n\nGuards Room.\n");
  add_item("plaque", "It reads:\n\nCaptain of the Front Gate.\n");
  
  add_exit(ERE_DIR + "lm1c5","north",0,1);
  add_exit(ERE_DIR + "lm1c1","south",0,1);
  add_exit(ERE_DIR + "lm1c4","east",0,1);
}
