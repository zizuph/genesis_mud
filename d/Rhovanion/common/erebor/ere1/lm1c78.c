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
  set_long("The tunnel here seems more or less cleaner that the rest of the "
         + "the tunnels around here, maybe it is because you're getting close "
         + "to the Guard HeadQuarters. "
         + "As you walk towards the gates west, the guards start to draw theire "
         + "weapons and look very suspiciously at you. There is crossing of the "
         + "tunnels from the north, east and west, to the east. You can see a  "
         + "iron gate to the west which blocks the entrance to the Guard  "
         + "HeadQuarters. ");

  add_exit(CAVE_DIR + "lm1c69","east",0,1);
  add_exit(CAVE_DIR + "lm1c77","west",0,1);

}
