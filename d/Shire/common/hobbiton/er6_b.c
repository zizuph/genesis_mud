inherit "/std/room";

#include "defs.h"

create_room() {
   set_short("Main road");
   set_long(
      "You are on the great Eastroad. Here the big road makes a big\n"
    + "turn northwest, and branches south. If you go east, you\n"
    + "will eventually get to Bree. If you go west, you will end\n"
    + "up in Grey Havens.\n");

   add_exit(STAND_DIR + "er5", "east", 0);
   add_exit(STAND_DIR + "er7", "northwest", 0);
   add_exit("/d/Shire/buckland/deepr1", "south", "@@my_south",0);
}
my_south()
  {
   if (this_player()->query_wiz_level())
   {
      write("Okiedokie.\n");
      if(this_player()->short())
         say(QCTNAME(this_player()) + " leaves into the unfinished area.\n");
      return 0;
   }
   write("South of here Buckland lies.\n"
       + "This is the land of bliss for all hobbits.\n"
       + "Unfortunately the road is blocked just now.\n"
       + "Come back later.\n");
   return 1;
}
