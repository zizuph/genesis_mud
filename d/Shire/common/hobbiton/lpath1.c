inherit "/std/room";

#include "defs.h"

create_room() {
   set_short("Little path");
   set_long(break_string(
      "You have strolled off into nature and find yourself on a little path "
    + "south of a big road. South you see a little cottage where smoke rises "
    + "from the chimney. East is a small clearing with a well.\n", 70));

   add_exit(STAND_DIR + "er12", "north", 0);
   add_exit(STAND_DIR + "wplace", "east", 0);
   add_exit(STAND_DIR + "forge", "south", 0);
}
