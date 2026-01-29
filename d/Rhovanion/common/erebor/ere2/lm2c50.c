inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("central");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("Here the corridor opens up to a small square. The building "
        +  "to the west has all signs of wealth, and that is even for "
        +  "a dwarf. From here you can catch a glimpse of a vault or so "
        +  "inside, so you correctly assume that it may be a bank or some"
        +  "thing similar.\n");
 
  add_exit(CAVE_DIR + "lm2c49","west",0,1);
  add_exit(CAVE_DIR + "lm2c53","south",0,1);
  add_exit(CAVE_DIR + "lm2c41","north",0,1);
}
