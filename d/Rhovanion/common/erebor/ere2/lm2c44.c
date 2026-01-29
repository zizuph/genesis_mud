inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{
  object door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("central");
  set_cave("Erebor");
  set_cave_type(6);
  set_long("To the north you can see the park open up, and "
        + "you can see glittering from water in the soft light. "
        + "To the west is darkness, and you cant see anything from here "
        + "in that direction.\n");

  add_exit(CAVE_DIR + "lm2c45","east",0,1);
  add_exit(CAVE_DIR + "lm2c43","west",0,1);
  add_exit(CAVE_DIR + "lm2c31","north",0,1);
}
