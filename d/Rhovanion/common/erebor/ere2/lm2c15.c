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
  set_long("As the rest of this park, this corner is filled "
        + "with beautifully carved rocks in different shapes. "
        + "You feel that you dont have to be a dwarf to "
        + "feel its beauty.\n");

  add_exit(CAVE_DIR + "lm2c16","east",0,1);
  add_exit(CAVE_DIR + "lm2c30","south",0,1);
}
