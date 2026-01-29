/*
 *  Path leading up the mountain
 */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "defs.h"

create_room() {
   set_short("Path");
   set_long("@@my_long");

   add_exit(BREE_DIR + "bridge1","south");
   add_exit(HINROOM_DIR + "path4","north");

   add_prop(ROOM_I_INSIDE, 0);  /* This room is outside */
   reset_room();
}

reset_room()
{
   if (!present("pawnrose",this_object()))
      clone_object(HERB_DIR + "pawnrose")->move(this_object());

   if (!present("rock") && random(4))
      clone_object(OBJ_DIR + "smallrock")->move(this_object());
}

my_long() {
   return break_string(
      "You are on a road in a gradually changing environment. "
    + "To the south the country is hilly, to the north and west "
    + "it gets rougher and more mountain-like.\n",70);
}
