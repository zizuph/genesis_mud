inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("western");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("This is the main east-west corridor on the second "
        + "level here in Erebor, and its well lit up "
        + "by huge torches sitting in large torchholders. "
        + "The corridor starts slowly to straighten out here. "
        + "Over to the west you can spot what seems to be some "
        + "stairs as well as some more passages leading north.\n");
 
  add_exit(CAVE_DIR + "lm2c25","east",0,1);
  add_exit(CAVE_DIR + "lm2c23","west",0,1);
  add_exit(CAVE_DIR + "lm2c40","south",0,1);
}
