inherit "/std/room";

#include "defs.h"

static object gorge,grimrock;

create_room() {
   set_short("Main road");
   set_long(break_string(
      "You are on the great Eastroad, south of a village. "
    + "The road seems fairly well used and stretches from east to west. "
    + "A yellow sign points north to a frequently "
    + "used road that leads to a big village in the distance.\n",70));

   add_exit(STAND_DIR + "er16", "east", 0);
   add_exit(STAND_DIR + "er20", "west", 0);
   add_exit(STAND_DIR + "er172", "north", 0);

   add_item(({"sign","yellow sign"}), "@@sign_long");


}

init() {
   ::init();
   add_action("do_read","read");
}

do_read(str) {
   if (str == "sign" || str == "yellow sign")
   {
      write(sign_long());
      return 1;
   }
   return 0;
}

sign_long() {
   return "The sign says: Hobbiton, 30 leagues.\n";
}
