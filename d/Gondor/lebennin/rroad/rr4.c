/*
 *	/d/Gondor/lebennin/rroad/rr4.c
 *
 *	Fourth room of the ring road leading around Pelargir.
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

   set_extraline("The city of Pelargir lies to the east, across a narrow "
      +	"field. It is possible to see birds flying above the city walls. "
      +	"The fields of Lebennin stretch out on the other side of the "
      + "road.");

   add_exit(LEB_DIR + "rroad/rr3", "south", 0, 2);
   add_exit(LEB_DIR + "rroad/rr5", "north", 0, 2);
     
    add_field();
    add_birds();
    add_road();
    add_city();
    add_walls("central");
}

