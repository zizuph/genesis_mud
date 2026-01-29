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
  set_long("You are standing in a corridor leading east and west. The corridor "
         + "continues both westward and eastwards. Eastwards leading towards "
         + "a crossing of this tunnel and two others. And westwards towards "
         + "a entrance to some Tavern. The crossing is "
         + "bathed in light from torches haning on the wall. From a doorway "
         + "to the east of here you can hear chatting and mumbling sounds of "
         + "several people.");
    
  add_exit(CAVE_DIR + "lm1c35","west",0,1);
  add_exit(CAVE_DIR + "lm1c38","east",0,1);

}
