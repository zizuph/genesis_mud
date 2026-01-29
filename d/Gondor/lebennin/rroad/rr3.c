/*
 *	/d/Gondor/lebennin/rroad/rr3.c
 *
 *	Third room of the ring road leading around Pelargir.
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

   set_extraline("The city of Pelargir lies to the east of here, behind the "
      +	"city walls. The southern arm of the Sirith flows south of here, "
      + "and it it possible to cross it by an old wooden bridge. "
      +	"Fields lie as far as the eye can see to the west.");

   add_exit(LEB_DIR + "rroad/rbdg1", "southeast", 0, 2);
   add_exit(LEB_DIR + "rroad/rr4", "north", 0, 2);
     
    add_field();
    add_birds();
    add_road();
    add_sirith("southcent", ({"southern arm", "arm", "south sirith"}));
    add_city();
    add_walls("central");
    add_bridge("south", ({"bridge"}));
}

