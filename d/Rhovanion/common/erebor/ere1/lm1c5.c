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
  set_long("Along the west wall runs "
         + "the River Running in a deep canal. In the east "
         + "wall you can see an opening. From the opening "
         + "comes a familiar smell, a stable perhaps? To "
         + "the south you can barely see the Front Gate and "
         + "the corridor continues north.");

  add_exit(CAVE_DIR + "lm1c2","south",0,1);
  add_exit(CAVE_DIR + "lm1c7","north",0,1);
  add_exit(CAVE_DIR + "lm1c6","east",0,1);
}
