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
  set_cave_type(7);
  set_long("This room is made for the guardpatrol. You can see, for "
        + "such rooms, the normal equipment. Beds, racks and nothing much "
        + "more.\n");
 
  add_exit(CAVE_DIR + "lm2c51","southeast",0,1);
  add_exit(CAVE_DIR + "lm2c27","northwest",0,1);
}
