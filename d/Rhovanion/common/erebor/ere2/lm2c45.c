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
  set_long("Here is the southeast corner of the park. "
        + "Exept from a small crack in the wall, nothing unusual "
        + "can be seen or heard.\n");

  add_item("crack","After a careful examination "
        + "you give up. There is nothing important with the "
        + "crack.\n");
 
  add_exit(CAVE_DIR + "lm2c44","west",0,1);
  add_exit(CAVE_DIR + "lm2c32","north",0,1);
}
