inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

create_cave()
{
  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("Along the north wall runs the River Running in "
         + "a deep canal. The corridor continues southwest "
         + "and east.");

  add_exit(ERE_DIR + "lm1c7","southwest",0,1);
  add_exit(ERE_DIR + "lm1c10","east",0,1);
}
