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
  set_long("You are standing in the northern parts of the Great "
         + "Hall. This magnificient hall continues further east "
         + "and south. Through the doorway to you north you can "
         + "see a big fireplace and a bar. A big sign towers over "
         + "the inviting opening. To your south lies the Well.");

  add_item("sign","The sign reads:\n\nThe Shield and Hammer!\n");

  add_exit(CAVE_DIR + "lm1c90","north",0,1);
  add_exit(CAVE_DIR + "lm1c15","south",0,1);
  add_exit(CAVE_DIR + "lm1c19","east",0,1);  
  add_exit(CAVE_DIR + "lm1c11","southwest",0,1);
}
