inherit "/d/Rhovanion/common/erebor/caves.c";

#include <stdproperties.h>
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_cave()
{
  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(3);
  set_long("This large room is rather damp and chilly. Along most "
	 + "walls there are shelves and on the floor there are some "
         + "casks and barrels. Your educated guess is that this a "
         + "storage-room of some sort.");

  add_prop(ROOM_I_LIGHT,0);

  add_exit(CAVE_DIR + "lm1c79","north",0,1);
}
