inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("western");
  set_cave("Erebor");
  set_cave_type(1);
  set_long(""
        + "The corridor looks the same as most corridors "
        + "here. Nothing much to examine for an experienced "
        + "adventurer like yourself.\n");
 
  add_exit(CAVE_DIR + "lm2c26","east",0,1);
  add_exit(CAVE_DIR + "lm2c24","west",0,1);
}
