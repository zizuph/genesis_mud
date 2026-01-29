inherit "/std/room";

#include "defs.h"

create_room() {
   set_short("Main road");
   set_long(
      "You are on the great Eastroad. The road is paved and looks\n"
    + "well-kept. If you follow this road to the east, you will\n"
    + "eventually get to Bree. If you go west, you will end up in\n"
    + "Grey Havens. North is the path to a small cabin.\n"
    + "There is a small mailbox here.\n");

   add_item("mailbox", "This is probably where the owner of the cabin\n"
	    + "to the north gets his mail delivered. A small sign on the\n"
	    + "mailbox says 'Raston Historican'.\n");

   add_exit(STAND_DIR + "er24", "east", 0);
   add_exit(STAND_DIR + "garden", "north", 0);
   add_exit(STAND_PARENT + "greyhaven/gh1", "west", 0);

}
