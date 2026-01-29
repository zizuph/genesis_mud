/*
 *	/d/Gondor/lebennin/rroad/rr1.c
 *
 *	First room of the ring road leading around Pelargir.
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
   
    set_extraline("The city of Pelargir lies close to the north and northeast, "
      +	"and between the road and the city walls is the southern "
      + "arm of the Sirith. "
      +	"The fields of Lebennin stretch out on the other side of the "
      + "road.");

    add_exit(LEB_DIR + "rroad/rr1", "southeast", 0, 2);
    add_exit(LEB_DIR + "rroad/rbdg1", "northwest", 0, 2);


    remove_item("road");
    remove_item("field");

    add_road();
    add_field();

    add_birds();
    add_sirith("south", ({"southern arm", "arm", "south sirith"}));
    add_city();
    add_walls("south");
    add_bridge("south");
    add_item(({"bridge", "stone bridge", "old bridge", "old stone bridge"}),BSN(
        "The road crosses the Sirith on an old stone bridge "
      + "just outside the city walls. The bridge is wide enough "
      + "for ox carts to use it. It spans the river in three arches "
      + "that rest on the banks of the river and on two mighty stone "
      +	"pillars built into the river. There is also a wooden bridge to "
      + "the northwest."));
    add_item(({"gate", "city gate", "city gates"}), BSN(
        "The south gates of Pelargir "
      +	"lie to the east of here, and it is possible to see the "
      +	"mighty towers which stand aside it."));
    add_item(({"towers", "tower"}), BSN("The towers straddling the south "
      + "gate of the city stand high above the rest of the walls. They "
      +	"appear to be able to withstand almost any attack.")); 

}

