/*
 * /d/Gondor/river/anduin/lorien2rauros/beach22w.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * beach at southern end of portage trail, 1 mile
 * below sarn gebir.
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";

#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	POOL	(LORIEN_TO_RAUROS_DIR+"pool22")

/* prototypes */
public void	create_shore_room();
public void	init();
public int	move_msg();

/*
 * Function name:	create_shore_room
 * Description	:	set up the beach
 */
public void
create_shore_room()
{
    set_short("stony beach");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"A smooth strip of gray stone forms a beach beside a shallow "+
	"pool. Inland, the land becomes more rugged; scree "+
	"lies jumbled beneath low limestone cliffs.  Beyond "+
	"the pool, the Great River flows south.");

    set_tod_landtype("beach");
    set_tod_landname("the Emyn Muil");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("east",
    	({ "calm pool", "calm shallow pool", "shallow pool",
	   "waters", "water", }) );

    add_exit("pool22", "east", 0, 2, 1);
    add_exit("portage8", "west", 0, 5);
    add_exit("pierwest", "southeast", move_msg, 2, 1);

    set_no_exit_msg( ({ "northeast", "north", }),
	BSN("The beach narrows quickly, leaving you no "+
	    "choice but to return to where you were."));
    set_no_exit_msg( ({ "south", "southwest", "northwest", }),
	BSN("You wander among the scree, but can find no path."));

    add_item( ({ "calm bay", "calm shallow pool", "shallow pool",
	   "waters", "water", "pool", }),
	&exa_water(POOL,
	    "The pool is shallow, and quite calm.\n"));
    add_item( ({ "west shore", "western shore", "west bank",
	"western bank", "river bank", "bank", "shore",
	"smooth strip", "strip", "stony beach", "beach" }),
	BSN("The beach is simply a smooth strip of stone at "+
	    "the edge of the pool. Inland, it quickly gives way to "+
	    "jumbled scree and weather-worn cliffs."));
    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", }),
	    BSN("To the east, beyond the pool, the Anduin flows "+
	    "swiftly south."));
    add_item( ({ "emyn muil", }),
	BSN("The cliffs of the Emyn Muil are barren, and "+
	    "worn by weather."));
    add_item( ({ "far side", "side", "far side of river",
	"eastern shore", "east shore", "eastern bank", "east bank", }),
	BSN("It is impossible to see the far side of the river from here."));
    add_item( ({ "stone", "gray stone", "ground" }),
	BSN("The stone of the beach is relatively smooth, but "+
	    "to the west the ground becomes rough and heaped "+
	    "with tumbled rocks and boulders."));
    add_item( ({ "low cliff", "low cliffs", "limestone cliff",
	"limestone cliffs", "cliff", "cliffs", }),
	BSN("The limestone cliffs show the effects of time and weather."));
    add_item( ({ "tumbled boulder", "tumbled boulders",
	"tumbled rock", "tumbled rocks", "boulder", "boulders",
	"rock", "rocks", "jumbled scree", "scree", }),
	BSN("Rocks and boulders of all sizes are tumbled below "+
	    "the cliffs."));

    set_drink_from( ({ "calm bay", "calm shallow pool", "shallow pool",
	   "pool", }) );

} /* create_shore_room */


/*
 * Function name:	init
 * Description	:	add drink verb
 */
public void
init()
{
    ::init();
    init_drink();
} /* init */


/*
 * Function name:	move_msg
 * Description	:	write a msg about struggling up the slope
 * Returns	:	0 (exit always allowed)
 */
public int
move_msg()
{
    WRITE("You scramble onto the stone pier.");
    return 0;
} /* move_msg */
