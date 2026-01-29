inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_cave()
{
  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(2);
  set_long("There's no way this place could be anything "
	 + "else than a stable. It's smelly, dirty and "
         + "occupied by horses!");

  add_item(({"horse","horses"}),"These are small horses "
         + "suitable to Dwarves.\n");

  add_exit(CAVE_DIR + "lm1c56","north",0,1);
}
