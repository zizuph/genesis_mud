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
  set_long("Even if there is no vegetation here "
        + "you can almost smell the rocks of this dwarven park. "
        + "If you didnt know better you could almost think it "
        + "was alive.\n");

  add_exit(CAVE_DIR + "lm2c15","west",0,1);
  add_exit(CAVE_DIR + "lm2c17","east",0,1);
  add_exit(CAVE_DIR + "lm2c31","south",0,1);
}
