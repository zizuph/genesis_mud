inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

create_cave()
{
  object door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(2);
  set_long("You are standing in the Great Hall just south of "
         + "the Well. The immense hall seems to go on forever "
         + "expanding to your north and east. There is "
         + "an opening to your south. It looks pretty dark and "
         + "scary.");

  add_exit(ERE_DIR + "lm1c11","northwest",0,1);
  add_exit(ERE_DIR + "lm1c15","north",0,1);
  add_exit(ERE_DIR + "lm1c17","east",0,1);  
  add_exit(ERE_DIR + "lm1c13","south",0,1);
}
