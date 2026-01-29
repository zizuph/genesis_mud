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
  set_cave_type(2);
  set_long("This large room is quite empty. Judging by the "
	 + "smell it seems like it is used as a stable but there "
         + "are no beasts around right now.");

  add_prop(ROOM_I_LIGHT,0);

  add_exit(CAVE_DIR + "lm1c7","southeast",0,1);
}
