inherit "/d/Gondor/lebennin/sroad/sroad.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_road()
{
   set_extraline("To the northeast the walls of Pelargir upon Anduin "
     + "can be seen. The city cannot be far from here. You also notice "
     + "a path to the east.");

   add_exit(LEB_DIR + "sroad/sr1", "northeast", 0, 2);
   add_exit(LEB_DIR + "sroad/south_pier", "south", 0, 2);
   add_exit(LEB_DIR + "sroad/sr3", "southwest", 0, 2);
   add_exit("/d/Gondor/pelargir/riverstead/room/entrance", "east", 0, 2);

   add_item(({"city","pelargir"}), BSN(
       "Pelargir upon Anduin, second largest city of Gondor and the "
     + "largest harbour of the realm, is not far from here to the "
     + "northeast. The road will lead you to the city gates."));

   add_anduin();
}

