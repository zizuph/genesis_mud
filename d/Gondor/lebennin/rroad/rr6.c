/*
 *	/d/Gondor/lebennin/rroad/rr6.c
 *
 *	Sixth room of the ring road leading around Pelargir.
 *
 *	copyright (C) Jim Fraser 03/11/95
 *
 * 	Some material taken from Olorin's south road. /lebennin/sroad/
 */
#pragma strict_types

inherit "/d/Gondor/lebennin/rroad/rroad.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_road()
{
   remove_item("road");

   set_extraline("The city of Pelargir is just to the southeast, and it is "
      +	"possible to see the northern gates from here, or at least the "
      + "towers defending them. "
      + "A narrow track leads north across the fields.");

   add_exit(LEB_DIR + "rroad/rr7", "northeast", 0, 2);
   add_exit(LEB_DIR + "rroad/rbdg2", "southwest", 0, 2);
   add_exit(SIRITH_DIR + "farms/fields/track1", "north", 0, 2);
     
    add_birds();
    add_road();
    add_sirith("north", ({"northern arm", "arm", "north sirith"}));
    add_city();
    add_walls("north");
    add_bridge("north",({"bridge"}));
    add_item(({"gates", "gate", "city gate", "city gates"}), BSN(
        "The north gates of Pelargir "
      +	"lie a little to the east of here, and it is possible to see the "
      +	"mighty towers which stand aside it."));
    add_item(({"towers", "tower"}), BSN("The towers straddling the north "
      + "gate of the city stand high above the rest of the walls. They "
      +	"appear to be able to withstand almost any attack.")); 
    add_item(({"north side","north side of road","field","fields"}), BSN(
        "The fields appear to be lying fallow."));
    add_item(({"narrow track","track"}), BSN(
        "The track doesn't appear to get much use."));

}
