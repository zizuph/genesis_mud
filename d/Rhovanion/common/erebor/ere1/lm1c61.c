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
  set_long("The corridor seems to expand further south as long as you can see. "
         + "To the north you notice that the corridor widens out into a huge "
         + "hall where the two main corridors of the mountain meets, you are "
         + "standing on the southern main corridor. From somewhere to the south "
         + "you can hear laughter and music, even further south will bring you "
         + "towards the Guard Headquaters.");

  add_exit(CAVE_DIR + "lm1c22","north",0,1);
  add_exit(CAVE_DIR + "lm1c64","south",0,1);
}
