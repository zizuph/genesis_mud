inherit "/std/room";

#include "/d/Shire/common/defs.h"

object ob;

create_room() {
   set_short("Main road");
   set_long(
      "You are on the great Eastroad. The road is paved and looks\n"
    + "well-kept. If you follow this road to the east, you will\n"
    + "eventually get to Bree. If you go west, you will end up in\n"
    + "Grey Havens.\n");
   add_exit(HOBBIT_DIR + "er1", "east", 0);
   add_exit(HOBBIT_DIR + "er4", "west", 0);

   reset_room();
}

reset_room() {

  if(!ob) {
    ob = clone_object(HOBBIT_DIR + "npc/quest_hobbit");
    ob->move(this_object());
  }
}
