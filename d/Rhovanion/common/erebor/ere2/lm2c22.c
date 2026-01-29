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
  set_long("This seems to be the end of this passage. "
        + "The stairs here leads down to what seems to be "
        + "the mines of Erebor. The stairs are blocked so you "
        + "cannot go down.\n");
 
  add_item("stairs","The stairs down to the mines are blocked "
        + "by huge boulders and bars. Impossible to pass.\n");

  add_item(({"bars","boulders"}),"The bars and boulders are huge "
        + "and too massive to break down. Typically dwarven made.\n");
 
  add_exit(CAVE_DIR + "lm2c23","east",0,1);
}
