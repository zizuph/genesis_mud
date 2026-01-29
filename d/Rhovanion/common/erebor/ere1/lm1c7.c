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
         + "the River Running in a deep canal. Crossing the "
         + "canal to northwest is a bridge hewn out of the "
         + "rock. There is nothing to greet you on the other "
         + "side but a big black hole. The Front Gate "
         + "lies further south and to the north you see the "
         + "corridor take a turn to the northeast.");

  add_exit(CAVE_DIR + "lm1c5","south",0,1);
  add_exit(CAVE_DIR + "lm1c8","northwest",0,1);
  add_exit(CAVE_DIR + "lm1c9","northeast",0,1);
}
