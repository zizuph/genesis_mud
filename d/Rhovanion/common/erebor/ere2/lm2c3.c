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
  set_long("This seems to be the end of this passage "
         + "as all you can see here is three houses. "
         + "There are no doors as usual to those houses.\n");

  add_exit(CAVE_DIR + "lm2c1","north",0,1);
  add_exit(CAVE_DIR + "lm2c2","west",0,1);
  add_exit(CAVE_DIR + "lm2c4","east",0,1);
  add_exit(CAVE_DIR + "lm2c6","south",0,1);
}
