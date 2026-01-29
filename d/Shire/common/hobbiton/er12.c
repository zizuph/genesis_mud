inherit "/std/room";

#include "defs.h"

create_room() {
   set_short("Main road");
   set_long(
      "You are on the great Eastroad. The road is paved and looks\n"
    + "well-kept. If you follow this road to the east, you will\n"
    + "eventually get to Bree. If you go west, you will end up in\n"
    + "Grey Haven. A little sign points south to a narrow road.\n");

   add_item(({"sign", "little sign"}),"@@sign_long");

   add_exit(STAND_DIR + "er11", "east", 0);
   add_exit(STAND_DIR + "er13", "west", 0);
}

init() {
   ::init();
   add_action("do_read","read");
}

do_read(str) {
   notify_fail("Read what?\n");
   if (str != "sign" && str != "little sign")
      return 0;
   write(sign_long());
   return 1;
}

sign_long() {
   return "The sign says: Fraymorton, 10 leagues\n"
        + "Peering south, you can make out a little village.\n";
}
