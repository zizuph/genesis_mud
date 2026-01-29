inherit "/std/room";

#include "/sys/stdproperties.h"
#include "defs.h"

object well_obj, bucket;

create_room() {
   set_short("Water place");
   set_long(break_string(
          "This little spot was probably made for tired travellers to rest. "
        + "There is a well here, and the grass looks soft enough to lie "
        + "down in.\n", 70));

   add_item("grass", "The grass looks soft. You feel like taking a nap here.\n");
   add_prop(OBJ_I_CONTAIN_WATER, 1);
;
   add_exit(STAND_DIR + "er11", "north", 0);
   add_exit(STAND_DIR + "lpath1", "west", 0);

   reset_room();
}

reset_room() {
   if (!well_obj) {
      well_obj = clone_object(STAND_OBJ + "well");
      well_obj->move(this_object());
   }

   if(!present("bucket"))
   {
    bucket = clone_object(OBJ_DIR + "bucket");
   bucket->move(TO);
   }
}
