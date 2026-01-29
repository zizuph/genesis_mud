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
  set_long("You can see that the corridor leads south towards a large hall in "
         + "the center of Lonely Mountain and north towards a crossing of this "
         + "corridor and two others. From somewhere to the south you can hear "
         + "laughter and singing flood out through a door in the east wall, "
         + "undoubtfully some sort of Tavern or Pub is located there. "
         + "From somewhere just to the north of here you can hear the sounds of "
         + "discussing and mumbling.");
  
  add_exit(CAVE_DIR + "lm1c38","north",0,1);
  add_exit(CAVE_DIR + "lm1c30","south",0,1);

}
