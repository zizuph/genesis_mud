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
  set_long("You wonder who can have created this park. "
        + "Judging from what you can see and feel, he must have "
        + "been a mighty good craftsman.\n");

  add_exit(CAVE_DIR + "lm2c16","west",0,1);
  add_exit(CAVE_DIR + "lm2c32","south",0,1);
}
