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
  set_long("This is the entrance to the park at the royal "
        + "castle. Unlike most parks, this one has no trees, "
        + "bushes or other growing things in it. "
        + "It is just made of rock. "
        + "\n");

  add_exit(CAVE_DIR + "lm2c15","north",0,1);
  add_exit(CAVE_DIR + "lm2c43","south",0,1);
  add_exit(CAVE_DIR + "lm2c29","west",0,1);
}
