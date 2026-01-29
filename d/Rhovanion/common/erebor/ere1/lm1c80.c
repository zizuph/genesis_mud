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
  set_long("Right infront of you there is a entrance to some sort of drinking "
         + "place, or atleast it smells and sounds so. Different odours of sweat "
         + "beer and something undescribable wafts out from the doorway to the north. "
         + "Maybe you have found the Pub the guards uses. You can go west "
         + "down the tunnel towards a crossing of the tunnels from the north, east "
         + "and west. Further west you can see the closed gate which leads into "
         + "the Guard HeadQuarters. "
         + " ");
  
  add_exit(CAVE_DIR + "lm1c81","north",0,1);
  add_exit(CAVE_DIR + "lm1c79","west",0,1);

}
