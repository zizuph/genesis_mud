inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_cave()
{
  object door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(2);
  set_long("You are standing in the Great Hall. Under your "
         + "feets you can hear the sound of water flowing. "
         + "The hall is huge, and lit by oil-lamps leaving "
         + "you with a nice cosy feeling. To the north you "
         + "can see an opening. To your east there is a "
         + "hole in the floor sorrounded by a brass fence. The "
         + "vast hall continues east, northeast and southeast. "
         + "Through an opening in the west wall you can see "
         + "a well-lit corridor.");

  add_exit(CAVE_DIR + "lm1c10","west",0,1);
  add_exit(CAVE_DIR + "lm1c12","north",0,1);
  add_exit(CAVE_DIR + "lm1c15","east",0,1);  
  add_exit(CAVE_DIR + "lm1c16","northeast",0,1);
  add_exit(CAVE_DIR + "lm1c14","southeast",0,1);
}
