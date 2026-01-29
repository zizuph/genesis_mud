/*
 * /d/Gondor/river/anduin/lorien2rauros/beach06w.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 105 miles south of silverlode, the campsite for day 3.
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";

#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	RIVER	(LORIEN_TO_RAUROS_DIR+"river06")

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
	"A narrow strip of gravel runs alongside the river. "+
	"To the east, the deep waters of the Anduin roll past. "+
	"To the west, flat treeless plains stretch to the horizon.");
    set_tod_landname("the Brown Lands");
    set_tod_landtype("beach");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("east",
	({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );

    add_exit("river06", "east", 0, 2, 1);
    set_no_exit_msg( ({ "northeast", "north", "northwest", "west",
    	"southwest", "south", "southeast", }),
	BSN("You wander for a while along the edge of the plains, "+
	    "but the featureless land is strangely disorienting. "+
	    "You retreat to the beach."));

    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", "waters", "water", }),
	&exa_water(RIVER,
	    "The Anduin appears to be quite deep, and its waters "+
	    "flow swiftly from northwest to southeast.\n"));

    add_item( ({ "beach", "narrow strip of gravel", "strip of gravel",
	"narrow strip", "strip", }),
	BSN("The beach is just a flat strip of gravel, perhaps "+
	    "four feet wide."));
    add_item( ({ "coarse gravel", "gravel", "ground", "dirt" }),
	BSN("Coarse gravel covers the beach."));

    add_item( ({ "long formless slopes", "formless slopes", "slopes",
	"slope", "eastern bank", "east bank", "far shore", "far side",
	"far side of river", "eastern shore", "east shore" }),
	BSN("On the eastern shore, long formless slopes stretch up "+
	    "and away from the river."));
    add_item( ({ "this shore", "this side", "this side of river",
	"western bank", "west bank", "western shore", "west shore" }),
	BSN("On this side of the river, the land is flat and in many "+
	    "places green with wide plains of grass."));
    add_item( ({ "brown lands", "river bank", "river banks", "banks",
	"bank", "land", "terrain", "shore", "shores" }),
	BSN("The shores are bare. On the eastern shore, the land "+
	    "slopes up from the river; on this side of the river, "+
	    "the terrain is flat."));
    add_item( ({ "featureless plains", "flat treeless plains",
	"treeless plains", "flat plains", "plains" }),
	BSN("Featureless plains stretch west as far as the eye can see."));
    add_item( ({ "tall grass", "tall grasses", "grasses", "grass", }),
	BSN("Tall grasses, green and swaying lightly with passing "+
	    "breezes, cover the plains."));

    set_drink_from( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", }) );
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
