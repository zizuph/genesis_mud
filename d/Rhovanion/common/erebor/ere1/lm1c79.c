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
  set_long("The corridor seems to expand towards the east and west. Westward "
         + "you can see a crossing of tunnels, further westward you see the gate "
         + "leading to the Guard HeadQuarters. From the east you can hear the "
         + "sounds of laughter and singing flushing out from a doorway in the "
         + "northern wall, obviously one of the infamous pubs must be located "
         + "there. Immediately to your south you see a small door, leading into "
         + "utter daarkness. ");
           
  add_exit(CAVE_DIR + "lm1c82","south",0,1);
  add_exit(CAVE_DIR + "lm1c69","west",0,1);
  add_exit(CAVE_DIR + "lm1c80","east",0,1);

}
