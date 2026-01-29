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
         + "Looking north you notice that the corridor seems to widen out into "
         + "a large hall. "
         + "Sounds of laughter and singing can be heard through the doorway to "
         + "the west, obviously some sort of pub is located there. You see a "
         + "small sign hanging right above the entrance. \n"
         + "Even more sounds of laughter and singing can be heard flushing out "
         + "of a doorway in the wall south of here, maybe another pub?\n"
         + "If you choose to go even further south it will bring you "
         + "towards the Guard Headquaters.");

  add_item("sign",BS(
    "The sign reads:\n"
  + "\n"
  + "Welcome visitor to the Broken Mug Pub, may your visit be ... profitable! "
  + "\n"
  + "\n"));
  
  add_exit(CAVE_DIR + "lm1c61","north",0,1);
  add_exit(CAVE_DIR + "lm1c63","west",0,1);
  add_exit(CAVE_DIR + "lm1c66","south",0,1);
}
