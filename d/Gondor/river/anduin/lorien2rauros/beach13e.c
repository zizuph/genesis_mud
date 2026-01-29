/*
 * /d/Gondor/river/anduin/lorien2rauros/beach13e.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * across from the eyot that is the day 6 campsite,
 *	"Long stony beaches lie to the east ..."
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";

#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	RIVER	(LORIEN_TO_RAUROS_DIR+"river13e")

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
    set_short("stony beach");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"A low shelf of stone forms a narrow beach. "+
	"To the west, the broad waters of the Anduin roll past. "+
	"To the east, the land rises to a bleak, wind-swept plain.");
    set_tod_landname("the Downs");
    set_tod_landtype("beach");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("west",
	({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );

    add_exit("river13e", "west", 0, 2, 1);
    set_no_exit_msg( ({ "north", }),
	BSN("You wander north a bit, but the beach narrows rapidly "+
	    "and you are forced to retreat."));
    set_no_exit_msg( ({ "south", }),
	BSN("You try to explore the beach to the south, but it "+
	    "ends abruptly. You return to your starting point."));
    set_no_exit_msg( ({ "northwest", "southwest" }),
	BSN("The beach is too narrow to permit travel in that "+
	    "direction."));
    set_no_exit_msg( ({ "northeast", "east", "southeast" }),
	BSN("You trudge up towards the plain, but it is bleak and "+
	    "apparently without end. Discouraged, you return to "+
	    "the beach."));

    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river" }),
	&exa_water(RIVER,
	    "In mid-river to the west is a low eyot. Beyond it, "+
	    "the hills of the western shore are barely visible.\n"));
    add_item( ({ "waters", "water", }),
	&exa_water(RIVER,
	    "The waters of the Anduin are broad and swift, and "+
	    "scattered shoals cause gentle ripples as they flow "+
	    "south.\n"));

    add_item( ({ "low shelf", "shelf", "stone shelf", "beach",
	"stony beach", "narrow beach", }),
	BSN("A narrow strip of gray stone runs just along the edge of the "+
	    "river."));
    add_item( ({ "narrow strip", "gray stone", "stone", "ground" }),
	BSN("The stone is dark gray, and appears quite hard."));
    add_item( ({ "river's surface", "water's surface", "surface", "gravel",
	"shoals", "gravel-shoals" }),
	BSN("Long shoals of gravel lie just below the river's surface."));
    add_item( ({  "shore", "shores", "river bank", "river banks",
	"bank", "banks", "western shore",
	"western bank", "west shore", "west bank", }),
	BSN("Far across the Anduin, hills rise on the western shore."));
    add_item( ({ "island", "small eyot", "eyot" }),
	BSN("The eyot, small and covered with scrubby bushes, "+
	    "lies not much above the level of the river."));
    add_item( ({ "scrubby bush", "scrubby bushes", "bush", "bushes" }),
	BSN("The bushes seem to cover most of the eyot, but it is "+
	    "difficult to see details from here."));
    add_item( ({ "hill of the western shore", "western hill",
    	"hills of the western shore", "western hills", "hill", "hills"}),
	BSN("The hills of the western shore are impossible to see "+
	    "clearly from here."));
    add_item( ({ "east shore", "eastern shore", "land", "down",
	"downs", "wold", "wolds" }),
	BSN("Beyond the beach, the eastern shore climbs steeply "+
	    "to a high plain, over which flows a chill "+
	    "air from the East."));
    add_item( ({ "high plain", "high plains", "bleak plain",
	"bleak plains", "wind-swept plain", "wind-swept plains",
	"bleak wind-swept plain", "bleak wind-swept plains",
	"plain", "plains", "east", "the east" }),
	BSN("A chill wind scours the plain, which appears bleak "+
	    "and unwelcoming."));

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
