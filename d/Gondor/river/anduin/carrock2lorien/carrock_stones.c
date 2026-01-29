/*
 * /d/Gondor/river/anduin/lorien2rauros/carrock_stones.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * on the stones in the carrock ford
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";

#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	RIVER	(CARROCK_TO_LORIEN_DIR + "river00")

/* prototypes */
public void	create_shore_room();
public void	init();

static object	River;		/* the river room */


/*
 * Function name:	create_shore_room
 * Description	:	set up the stones
 */
public void
create_shore_room()
{
    set_short("on a stone in the Carrock ford");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"This is one in a line of huge flat stones that have been " +
	"planted in the Anduin to provide a route from the Carrock " +
	"to the east shore.");
    set_tod_prependshort(1);
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("stones");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    add_exit("fishcamp_n", "east", 0, 2, 1);
    add_exit("carrock_beach", "west", 0, 2, 1);
    add_exit("river00", "south", 0, 2, 1);
    add_exit("river00", "down", 0, 2, 1);

    set_water("south",
	({ "ford", "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );

    set_drink_from( ({ "ford", "great river", "river anduin",
	"anduin river", "anduin", "river", }) );

    add_item( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }),
	&exa_water(RIVER, 
	    "Shallow waters gurgle and splash past the stones. " +
	    "To the southwest, the river deepens and flows more " +
	    "swiftly.\n"));

    add_item( ({ "route", "line of stones", "line", "huge flat stone", 
	"huge flat stones", "huge stone", "huge stones", "flat stone",
	"flat stones", "stone", "stones", }),
	BSN("The stones are quite flat, and each one is easily three " +
	    "feet wide. They make it possible to cross the Anduin " +
	    "dryshod."));
    add_item( ({ "ford", "carrock ford", }),
	BSN("Huge stones have been planted in the river here, " +
	    "allowing passage from the east shore to the Carrock."));
    add_item( ({ "land", "view", "vale", "inland", "river bank",
	"river banks", "bank", "banks", "shore", "shores",
	"west grasslands", "western grassland", 
	"east grasslands", "eastern grassland", 
	"wide grassland", "wide grasslands", "grassland", "grasslands", }),
	BSN("Tall grasses, green flecked with gold, stretch " +
	    "away from the river."));
    /* XXX actually the east *shore* is beach. beyound it is grass */
    add_item( ({ "near shore", "near side", "eastern horizon",
	"east horizon", "horizon", "eastern bank", "east bank",
	"eastern shore", "east shore", }),
	BSN("XXXThe eastern shore is carpeted with thick green grasses."));
    add_item( ({ "western bank", "west bank", "western shore",
	"west shore", }),
	BSN("Immediately to the west, the Carrock juts out of the Great " +
	    "River. On the far shore, wide grassland stretches away west."));
    add_item( ({ "far shore", "far side", "west horizon",
	"western horizon",  }),
	BSN("Thick green grass stretches as far as the eye can see."));
    add_item( ({ "tall grass", "tall grasses",
	"thick grass", "thick grasses", "thick green grass",
	"thick green grasses", "green grass", "green grasses",
	"grass", "grasses", }),
	BSN("The grasses grow waist-high, thick and sparsely flecked " +
	    "with gold."));
    add_item( ({ "tips", "flecks", "gold", }),
	BSN("Flecks of gold sparkle on the very tips of the grass."));

    add_item( ({ "great rock", "rock", "massive hill", 
	"massive hill of stone", "hill of stone", "hill", "carrock", }),
	BSN("The Carrock juts out of the river, a massive hill of stone. " +
	    "A path climbs from the water and disappears around the " +
	    "side of the rock."));
    add_item( ({ "side", "well worn path", "path", }),
	BSN("A well worn path climbs from the water up and " +
	    "around the Carrock."));
    add_item( ({ "hilltop", "hill top", "top", }),
	BSN("The top of Carrock is quite flat, and reasonably wide."));
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
