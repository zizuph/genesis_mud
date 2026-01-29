/*
 *	/d/Gondor/lebennin/rroad/rr5.c
 *
 *	Fifth room of the ring road leading around Pelargir.
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

   set_extraline("The city of Pelargir is just behind the walls to the "
      +	"east of here. The northern arm of the river Sirith crosses a small "
      + "wooden bridge to the northeast, and gulls can be seen overhead. "
      +	"The fields of Lebennin stretch out west of the road.");

   add_exit(LEB_DIR + "rroad/rbdg2", "northeast", 0, 2);
   add_exit(LEB_DIR + "rroad/rr4", "south", 0, 2);
     
    add_field();
    add_birds();
    add_road();
    add_sirith("northcent", ({"northern arm", "arm", "north sirith"}));
    add_city();
    add_walls("central");
    add_bridge("north",({"bridge"}));
}

