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
  set_long("You have come to the intersection of four tunnels. Nothing much can "
         + "be seen here, except the small torches on the walls providing the  "
         + "light here in the tunnel. You can hear speaking from the south and "
         + "by looking that way you notice several dwarven guards sitting around "
         + "a table. Towards the east you can hear singing and laughter, must be "
         + "another Pub or tavern in that direction. Looking west you see the  "
         + "gate which leads into the Guard HeadQuarters. ");
  
  add_exit(CAVE_DIR + "lm1c68","north",0,1);
  add_exit(CAVE_DIR + "lm1c83","south",0,1);
  add_exit(CAVE_DIR + "lm1c78","west",0,1);
  add_exit(CAVE_DIR + "lm1c79","east",0,1);

}
