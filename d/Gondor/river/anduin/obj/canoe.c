/*
 * /d/Gondor/river/anduin/obj/canoe.c
 *
 * A canoe built by Kolya.
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/boat";

#include <stdproperties.h>
#include "/d/Gondor/std/water/boat.h"
#include "/d/Gondor/defs.h"
#include "../anduin.h"

#define	INSIDE_CANOE_FILE	(RIVER_ANDUIN_DIR+"obj/inside_canoe")

/* prototypes */
public void	create_boat();


/*
 * Function name:	create_boat
 * Description	:	set up the canoe
 */
public void
create_boat()
{
    set_name( ({ "canoe", "boat" }) );
    set_adj("slender");
    set_short("slender canoe");
    set_long(BSN("The canoe is built of bark, stretched "+
	"over a wooden frame. It appears very graceful."));
    set_capacity(4);
    set_inside_boat(INSIDE_CANOE_FILE);

    add_item( ({ "bark covering", "covering", "bark", }),
	BSN("The bark is all of one piece. It "+
	    "wraps tightly around the frame of the canoe."));
    add_item( ({ "slender curved ribs", "curved ribs", "ribs",
	"frame", "wooden frame" }),
	BSN("Slender curved ribs arch against the bark covering "+
	    "of the canoe."));

    /* "a 4.2 metre canoe weighing some 22.7 kg could easily be carried"
     * if we say it's 13 feet long, 1 foot high, 3 feet wide at
     * midsection but tapering sharply to a point at each end,
     * so 1.5 feet wide on average, then it's 19.5 cubic feet
     */
    add_prop(OBJ_I_WEIGHT, 22700);
    add_prop(OBJ_I_VOLUME, 552252);
} /* create_boat */
