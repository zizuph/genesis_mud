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
  set_long("You have reached the end of the corridor and are now standing just "
         + "outside the entrance to a Tavern. Sounds of music and laughter flood "
         + "towards you and you feel a sudden urge to enter the tavern to get a "
         + "nice refreshing drink, or maybe ten. You spot a small sign hanging "
         + "above the door frame.");
   
  add_item("sign","Welcome Traveller to the Obnoxious Stag!\n");

    
  add_exit(CAVE_DIR + "lm1c33","west",0,1);
  add_exit(CAVE_DIR + "lm1c35","east",0,1);
  
}
