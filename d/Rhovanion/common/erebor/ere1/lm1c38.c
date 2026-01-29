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
  set_long("You have reached a crossing in the tunnels. From this point the "
         + "tunnels continue both south, west and east. From somewhere to the "
         + "west you can hear the faint sounds of singing and laughter, maybe "
         + "a tavern is somewhere in that direction. Nothing can be heard from "
         + "the tunnel to the east, actually it seems just to quiet. Immideately "
         + "to the north you see the entrance to a guard room, from this point "
         + "you can see that there is atleast four dwarven guards in the room. "
         + "The tunnel south leads towards the large hall in the center of "
         + "Lonely Mountain.");

  
  add_exit(CAVE_DIR + "lm1c32","south",0,1);
  add_exit(CAVE_DIR + "lm1c37","west",0,1);
  add_exit(CAVE_DIR + "lm1c39","north",0,1);
  add_exit(CAVE_DIR + "lm1c40","east",0,1);

}
