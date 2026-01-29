inherit "/std/room";

#include "defs.h"

create_room() {
   set_short("Main road");
   set_long(
      "You are on the great Eastroad. This is where the Eastroad\n"
    + "splits in two. One road leads south, and the other continues\n"
    + "to go east. On the southside of the road is the village of Waymeet.\n"
    + "A tall signpost points in many directions here.\n");

   add_item(({"sign","signpost"}),
     "The signpost consists of three signs, pointing in different directions.\n"
   + "The sign pointing east says:\n"
   + "  Hobbiton, Fraymorton, Whitefarrows and Bree.\n"
   + "\n"
   + "The sign pointing south reads:\n"
   + "  Sarn Ford.\n"
   + "\n"
   + "The sign pointing west says:\n"
   + "  Grey Havens.\n");

   add_exit(STAND_DIR + "er21", "east", 0);
   add_exit(STAND_DIR + "er23", "west", 0);
   add_exit(STAND_DIR + "er23", "south", "@@not_ready");
}

not_ready() {
   write(break_string("A villager steps out to bar your way and says, \"Lord Dunstable is not allowing visitors yet!\"\n", 70));
   return 1;
}
