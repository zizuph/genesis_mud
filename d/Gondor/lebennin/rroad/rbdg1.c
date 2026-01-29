/*
 *      /d/Gondor/lebennin/rroad/rbgd1.c
 *
 *      Bridge over the south arm of the sirith on the ring road leading 
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
    set_areadesc("bridge");

    set_extraline("An old wooden bridge is crossing the river "
     + 	"Sirith here.");

    add_exit(LEB_DIR + "rroad/rr2", "southeast", 0, 2);
    add_exit(LEB_DIR + "rroad/rr3", "northwest", 0, 2);

    add_item(({"river","south sirith","sirith","southern arm","arm"}),BSN(
     	"The wide southern arm of the Sirith is crossed by a wooden "
     +	"bridge here. Looking east, it is possible to see the towers "
     +	"straddling the south gate of Pelargir, and the stone bridge which "
     +	"crosses the Sirith at the gate."));
    add_item(({"bridge", "wooden bridge", "old bridge"}),BSN(
	"The bridge here is quite wide, as it needs to cross the wide arm "
     +	"of the Sirith. Off to the east, the stone bridge is visible "
     +	"leading into Pelargir.")); 
    add_item(({"stone bridge","old stone bridge"}),BSN(
        "The road crosses the Sirith on an old stone bridge "
      + "just outside the city walls. The bridge is wide enough "
      + "for ox carts to use it. It spans the river in three arches "
      + "that rest on the banks of the river and on two mighty stone "
      +	"pillars built into the river."));
    add_item(({"gate", "city gate", "city gates","gates"}), BSN(
        "The south gates of Pelargir "
      +	"lie a little to the east of here, and it is possible to see the "
      +	"mighty towers which stand aside it."));
    add_item(({"towers", "tower"}), BSN("The towers straddling the south "
      + "gate of the city stand high above the rest of the walls. They "
      +	"appear to be able to withstand almost any attack.")); 
    add_walls("south");
    add_birds();

}

