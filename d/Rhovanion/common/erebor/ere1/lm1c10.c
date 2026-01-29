inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_cave()
{
  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("Along the north wall runs the River Running in "
         + "a deep canal. The flow of the river is quite "
         + "calm here, maybe you're close to it's source? "
         + "The corridor follows the canal east and west.");

  add_exit(CAVE_DIR + "lm1c9","west",0,1);
  add_exit(CAVE_DIR + "lm1c11","east",0,1);
}
