inherit "/d/Shire/room";

#include "defs.h"

static object gorge,grimrock;



create_room() {

   set_short("Main road");
   set_long(
      "You are on the great Eastroad. The road is paved and looks\n"
    + "well-kept. If you follow this road to the east, you will\n"
    + "eventually get to Bree. If you go west, you will end up in\n"
    + "Grey Havens.\n");
   add_exit(HOBBIT_DIR + "er9", "east", 0);
   add_exit(HOBBIT_DIR + "er11", "west", 0);
  enable_reset();

}

