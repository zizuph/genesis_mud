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
  set_long("This corridor is a wide and well made one. From what "
        +  "you can see from here, it seems to be one of the main "
        +  "corridors on the second level. To the north you see the "
        +  "main junction and to the south you see some constructions "
        +  "that from this view seems to be facilities of some kind.\n");
 
  add_exit(CAVE_DIR + "lm2c50","south",0,1);
  add_exit(CAVE_DIR + "lm2c27","north",0,1);
}
