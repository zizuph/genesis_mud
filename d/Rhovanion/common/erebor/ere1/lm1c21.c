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
  set_long("The corridor seems to expand as you look to your west. Also "
         + "to your west there is a down stairscase. Further east lies "
         + "the intersection of the two major corridors here in the "
         + "mountain, known as the Place of the Guards. "
         + "Continuing east will eventually take you to the East Gate.");

  add_exit(CAVE_DIR + "lm1c20","west",0,1);
  add_exit(CAVE_DIR + "lm1c22","east",0,1);
}
