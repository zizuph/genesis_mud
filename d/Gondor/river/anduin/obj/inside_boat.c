/*
 * /d/Gondor/river/anduin/obj/inside_boat.c
 *
 * The room inside a boat of the fishcamp
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
 * Description	:	set up the boat
 */
public void
create_inside_boat()
{
    add_item( ({ "boat",  }),
	BSN("The sides of the boat curve gently up and inward, and the "+
	    "painted planks are very smooth."));
    add_item( ({ "side", "sides", }),
	BSN("The sides of the boat are fairly low, and gently curved."));
    add_item( ({ "misty grey paint", "grey paint", "grey planks",
	"misty grey planks", "misty grey plank", "grey plank",
	"plank", "planks", }),
	BSN("The planks have been sanded smooth and painted " +
	    "a grey that recalls mists at dawn."));

    set_min_boat_skill(20);	/* XXX  ?? */
    set_max_current(7);
} /* create_inside_boat */
