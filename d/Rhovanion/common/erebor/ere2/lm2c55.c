inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("southern");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("The corridor continues in a north-south direction, and there "
        +  "is an intresting looking building to the east.\n");
 
  add_exit(CAVE_DIR + "lm2c56","east",0,1);
  add_exit(CAVE_DIR + "lm2c58","south",0,1);
  add_exit(CAVE_DIR + "lm2c53","north",0,1);
}
