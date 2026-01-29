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
  set_long("This is another unfinished part of this mountain. "
        +  "This deadend is nothing but that. A deadend!\n");
 
  add_exit(CAVE_DIR + "lm2c40","north",0,1);
}
