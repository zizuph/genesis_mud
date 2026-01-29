inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{
  object door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("The corridor seems to be leading "
        + "to some houses further north.\n");

  add_exit(CAVE_DIR + "lm2c9","north",0,1);
  add_exit(CAVE_DIR + "lm2c14","south",0,1);
}
