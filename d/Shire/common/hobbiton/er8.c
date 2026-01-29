inherit "/std/room";

#include "defs.h"

create_room() {
   set_short("Main road");
   set_long(
      "You are on the great Eastroad. The road is paved and looks\n"
    + "well-kept. If you follow this road to the east, you will\n"
    + "eventually get to Bree. If you go west, you will end up in\n"
    + " Grey Havens. Here the road cuts the village Whitefurrows\n"
    + "in half. North of the road are grassy fields.\n");
   add_exit(STAND_DIR + "er7", "east", 0);
   add_exit(STAND_DIR + "er9", "west", 0);
     add_exit(STAND_DIR + "field1", "north", 0, 2);
   add_exit(STAND_DIR + "wf_south", "south", 0);
}
