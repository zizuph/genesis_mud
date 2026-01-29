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
  set_long("As you walk down the corridor you start to wonder if there is "
         + "nothing else but Pub's and Taverns in this mountain, and seconds "
         + "after you hear sounds of laughter and singing through the doorway "
         + "to the east, obviously some sort of pub is located there."
         + "You see a small sign hanging right above the entrance. "
         + "Even more sounds of laughter and singing can be heard flushing out "
         + "of a doorway in the wall south of here, maybe another pub? - "
         + "The corridor seem to widen out further to the south and northward "
         + "it leads to a crossing of this tunnel and two others.");

  add_item("sign",BS(
    "The sign reads:\n"
  + "\n"
  + "Welcome visitor to the Invinsible Drinker"
  + "\n"
  + "\n"));
  
  add_exit(CAVE_DIR + "lm1c28","south",0,1);  
  add_exit(CAVE_DIR + "lm1c32","north",0,1);
  add_exit(CAVE_DIR + "lm1c31","east",0,1);

}
