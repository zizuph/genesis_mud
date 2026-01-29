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
  set_cave_type(5);
  set_long("The room belongs to a strange "
         + "house here, that "
         + "is full of weird toys. When you look at them, "
        + "its hard to estimate what they are used for.\n");

  add_item(({"toys","toys"}),"The toys seems to be worthless for you. \n");

  add_exit(CAVE_DIR + "lm2c3","west",0,1);
}
