/*
 * /d/Gondor/river/anduin/obj/inside_canoe.c
 *
 * The room inside a canoe built by Kolya.
 *
 * TBD:	skill required, etc?
 */

#pragma strict_types

inherit "/d/Gondor/std/water/inside_boat";

#include <stdproperties.h>
#include "/d/Gondor/std/water/boat.h"
#include "/d/Gondor/defs.h"
#include "../anduin.h"


/* prototypes */
public void	create_inside_boat();


/*
 * Function name:	create_inside_boat
 * Description	:	set up the canoe
 */
public void
create_inside_boat()
{
    add_item( ({ "canoe",  }),
	BSN("The sides of the canoe curve gently up and inward, and the "+
	    "interior is lined with very thin, wide wood sheathing."));
    add_item( ({ "side", "sides", }),
	BSN("The sides of the canoe are fairly low, and gently curved."));
    add_item( ({ "interior", "lining", "wood sheathing", "sheathing", }),
	BSN("The lining is very thin, but flexible and apparently "+
	    "quite durable."));

    set_min_boat_skill(20);	/* XXX  ?? */
    set_max_current(7);
} /* create_inside_boat */
