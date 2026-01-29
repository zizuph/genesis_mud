inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "defs.h"

create_room() {



   set_short("East road");
   set_long(
      "You are on the great Eastroad. The road is paved and looks\n"
    + "well-kept. If you follow this road to the east, you will\n"
    + "eventually get to Bree. If you go west, you will end up in\n"
    + "Grey Havens. South is a clearing with a well in the middle.\n");
   add_exit(STAND_DIR + "er10", "east", 0);
   add_exit(STAND_DIR + "er12", "west", 0);


}
