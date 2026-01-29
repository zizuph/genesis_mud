/*
 * /d/Gondor/river/anduin/obj/boat.c
 *
 * Boat for the fishcamp
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/boat";

#include <stdproperties.h>
#include "/d/Gondor/std/water/boat.h"
#include "/d/Gondor/defs.h"
#include "../anduin.h"

#define	INSIDE_FILE	(RIVER_ANDUIN_DIR+"obj/inside_boat")

/* prototypes */
public void	create_boat();


/*
 * Function name:	create_boat
 * Description	:	set up the boat
 */
public void
create_boat()
{
    set_name( ({ "boat", "boat" }) );
    set_adj( ({ "sturdy", "grey" }) );
    set_short("sturdy grey boat");
    set_long(BSN("The boat is made of planks, fitted tightly " +
	"together and painted a misty grey. It looks sturdy, " +
	"but yet graceful."));
    set_capacity(4);
    set_inside_boat(INSIDE_FILE);

    add_item( ({ "misty grey paint", "grey paint", "paint",
	"grey planks", "misty grey planks", "misty grey plank",
	"grey plank", "plank", "planks", }),
	BSN("The planks have been sanded smooth and painted " +
	    "a grey that recalls mists at dawn."));


    /* "a 4.2 metre canoe weighing some 22.7 kg could easily be carried"
     * if we say it's 13 feet long, 1 foot high, 3 feet wide at
     * midsection but tapering sharply to a point at each end,
     * so 1.5 feet wide on average, then it's 19.5 cubic feet
     * of course, boats of wood probably weigh a bit more than
     * canoes, but what the heck ... 50 lbs is enough
     */
    add_prop(OBJ_I_WEIGHT, 22700);
    add_prop(OBJ_I_VOLUME, 552252);
} /* create_boat */
