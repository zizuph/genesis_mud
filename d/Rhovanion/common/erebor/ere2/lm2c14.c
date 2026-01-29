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
  set_cave_type(1);
  set_long("The corridor is not much different from any of the "
        + "corridors you have seen here.\n");

  add_exit(CAVE_DIR + "lm2c12","north",0,1);
  add_exit(CAVE_DIR + "lm2c27","south",0,1);
}
