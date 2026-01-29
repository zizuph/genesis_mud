inherit "/std/room";

#include "defs.h"

create_room() {
   set_short("Main road");
   set_long(break_string(
      "You are on the great Eastroad. The road is paved and looks "
    + "well-kept. If you follow this road to the east, you will "
    + "eventually get to Bree. If you go west, you will end up in "
    + "Grey Havens.\n",70));
   add_exit(STAND_DIR + "er18", "east", 0);
   add_exit(STAND_DIR + "er20", "west", 0);

   reset_room();
}

reset_room() {
   if (!present("rock"))
      clone_object(STAND_OBJ + "smallrock")->move(this_object()); 
}
