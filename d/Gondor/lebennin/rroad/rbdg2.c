/*
 *      /d/Gondor/lebennin/rroad/rbgd2.c
 *
 *      Bridge over the north arm of the sirith on the ring road leading 
 *	around Pelargir.
 *
 *      copyright (C) Jim Fraser 03/11/95
 *
 *      Some material taken from Olorin's south road. /lebennin/sroad/
 */
inherit "/d/Gondor/lebennin/rroad/rroad.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_road()
{
   ::create_road;

   set_areadesc("bridge");

   set_extraline("An old wooden bridge is crossing the river "
     + "Sirith here. A small path leads to the south.");

   add_exit(LEB_DIR+ "rroad/rr6", "northeast", 0, 2);
   add_exit(LEB_DIR + "rroad/rr5", "southwest", 0, 2);
   add_exit(LEB_DIR + "rroad/bridge", "south", 0, 2, 1);


    add_item(({"small path", "path"}), "The path leads down below the " +
        "bridge.\n");
    add_item(({"bridge", "wooden bridge", "old bridge", "old wooden bridge", }),
        BSN("The road crosses the Sirith on an old wooden bridge "
      + "just outside the city walls. The bridge is just wide enough "
      + "for ox carts to use it."));
    add_item(({"river","sirith","northern arm","north sirith","arm"}),BSN(
        "The northern arm of the Sirith is fairly deep but not very wide. "
      +	"It runs very quickly under the bridge and then under the city "
      +	"walls to the east."));
    add_walls("north");
    add_birds();
}
