/*
 *  A guard room in the Shire-mountain.
 */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "defs.h"

create_room() {
   set_short("Guard room");
   set_long(break_string(
      "This is a room where the guards hang out when they are not on duty. "
    + "Here they play cardgames and tell tales of the unknown. The room is "
    + "sober and cold. The guards obviously do not lead a life of luxury.\n",70));

   add_exit(HINROOM_DIR + "hall3","east");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

   refresh_guards();
}

reset_room() {
   refresh_guards();
}

refresh_guards() {
   object guard;
   int rand;

   if(!present("puddifoot"))
   {
    guard = clone_object(NPC_DIR + "newhinguard");
    guard->move(TO);
   }
}
