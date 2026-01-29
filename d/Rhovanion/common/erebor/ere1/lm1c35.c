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
  set_long("The corridor leads east and west. Westwards you see the entrance to "
         + "some Tavern, eastwards will lead you towards a well lit crossing. "
         + "Immediately south there is an entrance to a dark room, strange smells "
         + "seems to creap out from there, smells of beer, food and other things. ");

    
  add_exit(CAVE_DIR + "lm1c34","west",0,1);
  add_exit(CAVE_DIR + "lm1c37","east",0,1);
  add_exit(CAVE_DIR + "lm1c36","south",0,1);
}
