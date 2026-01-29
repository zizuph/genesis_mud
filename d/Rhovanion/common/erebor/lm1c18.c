inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

create_cave()
{
  object door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(2);
  set_long("You are standing in the centre of the Great Hall. "
         + "The hall is huge, and lit by oil-lamps leaving "
         + "you with a nice cosy feeling. Peering upwards you "
         + "can see the walls arching in over you to finally "
         + "meet, at least 30 meters up. To your west there is "
         + "an opening in the floor sorrounded by a fence. Over "
         + "to your east there seems to be some stairs, leading "
         + "down. The vast hall continues in all directions.");

  add_exit(ERE_DIR + "lm1c15","west",0,1);
  add_exit(ERE_DIR + "lm1c19","north",0,1);
  add_exit(ERE_DIR + "lm1c20","east",0,1);  
  add_exit(ERE_DIR + "lm1c17","south",0,1);
}
