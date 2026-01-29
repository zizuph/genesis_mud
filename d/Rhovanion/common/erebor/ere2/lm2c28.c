inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{

  set_rock_type("dark granite");
  set_cave_name("the Lonely Mountain");
  set_region("western");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("This is the main east-west corridor on the second "
        + "level here in Erebor. "
        + "Another typical corridor in the Lonely mountain. "
        + "\n");
 
  add_exit(CAVE_DIR + "lm2c29","east",0,1);
  add_exit(CAVE_DIR + "lm2c27","west",0,1);
}
