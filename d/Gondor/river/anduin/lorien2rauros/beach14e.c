/*
 * /d/Gondor/river/anduin/lorien2rauros/beach14e.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * in the downs, ~20 miles downstream of the day 6 campsite, 
 * approaching the emyn muil
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";

#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	RIVER	(LORIEN_TO_RAUROS_DIR+"river14e")

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
	"A narrow strip of stone runs between the river to the "+
	"west and the steep, wind-scoured inland terrain.");
    set_tod_landname("the Downs");
    set_tod_landtype("beach");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("west",
	({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );

    add_exit("river14e", "west", 0, 2, 1);
    set_no_exit_msg( ({ "south", }),
	BSN("You wander south a bit, but the beach ends almost at once."));
    set_no_exit_msg(( { "north" }),
	BSN("You stroll north along the beach but it narrows sharply, "+
	    "leaving you no choice but to retrace your steps."));
    set_no_exit_msg( ({ "northwest", "southwest" }),
	BSN("The beach is too narrow to permit travel in that "+
	    "direction."));
    set_no_exit_msg( ({ "northeast", "east", "southeast" }),
	BSN("You climb towards the downs, but they rise always "+
	    "before you, chill and forbidding. Disheartened, you "+
	    "return to the beach."));

    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river" }),
	&exa_water(RIVER,
	    "The wide, swift waters of the Anduin roll south past "+
	    "the stony beach.\n"));
    add_item( ({ "wide waters", "swift waters", "wide, swift waters",
	"waters", "water", }),
	&exa_water(RIVER,
	    "The waters swirl over gravel shoals as the Anduin "+
	    "flows south.\n"));

    add_item( ({ "narrow strip", "strip", "strip of stone",
	"long narrow strip", "long strip", "dark gray stone",
	"gray stone", "stone", "ground", "narrow strip of stone",
	"beach", "stony beach", }),
	BSN("The beach is a long, narrow strip of dark gray stone."));
    add_item( ({ "river's surface", "water's surface", "surface", "gravel",
	"shoals", "gravel-shoals" }),
	BSN("Long shoals of gravel roil the waters of the Anduin."));
    add_item( ({  "shore", "shores", "river bank", "river banks",
	"bank", "banks", }),
	BSN("High, rolling downs rise on either side of the river."));
    add_item( ({  "rolling expanses", "treeless expanses", "expanses",
	"land", "wold", "wolds" }),
	BSN("Rolling, treeless expanses of withered grass stretch away "+
	    "to the horizon."));
    add_item( ({ "western shore", "western bank", "west shore",
	"west bank", }),
	BSN("Far across the Anduin, bare hills rise from the water."));
    add_item( ({ "bare hill", "bare hills", "western hill",
    	"western hills", "hill", "hills"}),
	BSN("The hills on the far side of the river appear quite barren, "+
	    "but they are difficult to see clearly from here."));
    add_item( ({ "eastern shore", "eastern bank", "east shore",
	"east bank", "steep terrrain", "steep inland terrain",
	"inland terrain", "wind-scoured inland terrain", "terrain",
	"wind-scoured terrain", }),
	BSN("High, treeless downs rise sharply from the stony beach."));
    add_item( ({ "high downs", "treeless downs", "high treeless downs",
	"downs", "the east", "east" }),
	BSN("The downs are bare of all but withered grass, and a cold "+
	    "wind rolls over them from the East."));
    add_item( ({ "withered grass", "grass" }),
	BSN("The grass appears to be dead."));

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
