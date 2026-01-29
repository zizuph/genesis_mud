/*
 *  Path leading to Hin Warrior Guild
 *  This room is loaded by /d/Shire/preload.c (because of Gwaihir)
 */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "defs.h"

create_room() {
   set_short("Path");
   set_long(break_string(
      "You are on a small path that winds through the rocky mountain. "
    + "On both sides of the path are huge rock formations that are "
    + "impossible to climb. South the path goes down the mountain, and "
    + "north the path goes up.\n",70));

   add_item(({"rock","rocks"}), break_string(
      "The rock formations aside the path are way too steep to climb. They "
    + "only leave two options to leave open: north and south.\n",70));

   add_exit(HINROOM_DIR + "cave_ent","north");
   add_exit(HINROOM_DIR + "path2","south");

   add_prop(ROOM_I_INSIDE, 0);  /* This room is outside */
   call_out("reset_room", 1);
}


reset_room()
{
   if (!find_living("gwaihir_eagle"))
      clone_object(NPC_DIR + "gwaihir")->move(this_object());

   if (!present("rock") && !random(3))
      clone_object(OBJ_DIR + "smallrock")->move(this_object());
}
