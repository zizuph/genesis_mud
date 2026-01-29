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

   set_extraline("The city of Pelargir is to the southeast and south, "
      +	"and it is possible to see the northern gates from here, or "
      + "at least the towers defending them. "
      +	"The fields of Lebennin stretch out on the other side of the "
      + "road.");

    add_exit(LEB_DIR + "road/nr18", "east", 0, 2);
    add_exit(LEB_DIR + "rroad/rr6", "southwest", 0, 2);
     
    add_field();
    add_birds();
    add_road();
    add_sirith("north", ({"northern arm", "arm", "north sirith"}));
    add_city();
    add_walls("north");
    add_bridge("north",({"bridge"}));
    add_item(({"gate", "city gate", "city gates"}), BSN(
        "The north gates of Pelargir "
      +	"lie a little to the east of here, and it is possible to see the "
      +	"mighty towers which stand aside it."));
    add_item(({"towers", "tower"}), BSN("The towers straddling the north "
      + "gate of the city stand high above the rest of the walls. They "
      +	"appear to be able to withstand almost any attack.")); 

}

