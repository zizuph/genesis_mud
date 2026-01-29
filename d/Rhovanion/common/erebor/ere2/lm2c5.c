inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{
  object door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(5);
  set_long("The room belongs to one of the small "
         + "houses inside The Lonely Mountain. This house "
         + "probably belongs to one of the richest dwarves here.\n");

  add_exit(CAVE_DIR + "lm2c6","east",0,1);
}
