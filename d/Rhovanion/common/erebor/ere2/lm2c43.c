inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{
  object door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("central");
  set_cave("Erebor");
  set_cave_type(6);
  set_long("This corner of the park is lying in shadows. The light "
        + "that spreads around the rest of this area, has difficulties "
        + "to find its way here.\n");

  add_exit(CAVE_DIR + "lm2c44","east",0,1);
  add_exit(CAVE_DIR + "lm2c30","north",0,1);
}
