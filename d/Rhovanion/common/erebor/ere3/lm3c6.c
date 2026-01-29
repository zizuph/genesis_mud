inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere3/"

void
create_cave()
{

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("central");
  set_cave("Erebor");
  set_cave_type(2);
  set_long("\n");
 
  add_exit(CAVE_DIR + "lm3c15","south",0,1);
  add_exit(CAVE_DIR + "lm3c7","east",0,1);
}
