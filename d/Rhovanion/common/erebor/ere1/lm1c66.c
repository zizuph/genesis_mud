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
         + "Immediately to the north you see lights flush out of a open doorway "
         + "and with it loud singing.\n"
         + "Sounds of laughter and singing can be heard through the doorway to "
         + "the east, obviously some sort of tavern is located there. You see a "
         + "small sign hanging right above the entrance. \n"
         + "The tunnel south will bring you towards the Guard HeadQuarters. ");

  add_item("sign",BS(
    "The sign reads:\n"
  + "\n"
  + "Welcome visitor to the Tavern of the Cavern."
  + "\n"
  + "\n"));
  
  add_exit(CAVE_DIR + "lm1c64","north",0,1);
  add_exit(CAVE_DIR + "lm1c67","east",0,1);
  add_exit(CAVE_DIR + "lm1c68","south",0,1);
}
