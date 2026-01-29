/*
 * /d/Gondor/river/anduin/lorien2rauros/beach10w.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 200 miles south of silverlode, the campsite for day 5.
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";

#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	RIVER	(LORIEN_TO_RAUROS_DIR+"river10")

/* prototypes */
public void	create_shore_room();
public void	init();

/*
 * Function name:	create_shore_room
 * Description	:	set up the beach
 */
public void
create_shore_room()
{
    set_short("narrow strip of gravel");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"This narrow strip of hard, bare ground is tucked between "+
	"the Anduin to the east and bare, wind-swept hills to "+
	"the west.");
    set_tod_landname("the Brown Lands");
    set_tod_landtype("beach");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("east",
	({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );

    add_exit("river10", "east", 0, 2, 1);
    set_no_exit_msg( ({ "northwest", "west", "southwest", }),
	BSN("You wander towards the hills, but they rise ever "+
	    "before you, bleak and apprently endless. "+
	    "Discouraged, you return to the beach."));
    set_no_exit_msg( ({ "north", "south", "northeast", "southeast" }),
	BSN("You wander along the beach for a bit, but "+
	    "find nothing of interest."));

    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", }),
	&exa_water(RIVER,
	    "To the east, the deep waters of the Anduin "+
	    "flow swift and silent.\n"));
    add_item( ({ "waters", "water", }),
	&exa_water(RIVER,
	    "The waters of the Anduin are dark, deep and silent.\n"));

    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"far shore", "far side", "east shore", }),
	BSN("Hills rise in crumpled folds on the far side of the river."));
    add_item( ({ "western bank", "west bank", "western shore",
	"this side", "near side", "this shore",
	"near shore", "west shore", }),
	BSN("From this narrow strip of flat ground, the land "+
	    "climbs west to bleak, chalky hills."));
    add_item( ({ "shore", "shores", "river bank", "river banks",
	"bank", "banks" }),
	BSN("The shores, bare of tree or shrub, rise on either side "+
	    "to chalky hills."));
    add_item( ({ "brown lands", "land", "chalky hills", "bleak hills",
	"wind-swept hills", "bare hills", "bare chalky hills",
	"hill", "hills" }), 
	BSN("The bare hills, scoured by wind, rise steeply up from "+
	    "the river."));
    add_item( ({ "rumpled folds", "folds" }),
	BSN("The hills curve like rumpled folds of heavy cloth."));
    add_item( ({ "meagre beach", "beach", "narrow strip", "strip", }),
	BSN("A very narrow strip of flat ground borders the "+
	    "river, providing a meagre beach. "+
	    "A few feet inland, the land rises sharply to bare "+
	    "chalky hills."));
    add_item( ({ "hard bare ground", "hard ground", "bare ground",
	"ground", "firmly-packed dirt", "bare dirt", "dirt", }),
	BSN("The ground is firmly-packed bare dirt. Nothing grows here."));

    set_drink_from( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", }) );
} /* create_onwater */


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
