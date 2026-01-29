/*
 * /d/Gondor/river/anduin/carrock2lorien/river07.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 175 miles south of the Carrock
 *
 */

#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_onwater";
inherit "/d/Gondor/common/lib/tod_descs";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/onwater.h"
#include "../anduin.h"

/* prototypes */
public void	create_anduin_onwater();


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO,
	"175 miles south of the Carrock.\n");
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The waters flow swiftly south past rolling grasslands.");
    set_tod_landname("the vale of Anduin");	/* XXX */
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* set up water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river",
	"anduin", "river anduin", "anduin river" }) );
    set_upstreamdir("north");
    set_downstreamdir("south");
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */

    add_exit("gladdenm", "north");
    set_distance("north", 40);
    add_exit("river08", "south");
    set_distance("south", 30);
    add_exit("riverbottom07", "down");
    /* no shore rooms for now */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The waters of the Great River are wide. They flow " +
	    "smoothly south, with little noise or turbulence."));
    add_item( ({ "land", "view", "vale", "inland", "river bank",
	"river banks", "bank", "banks", "shore", "shores", }),
	BSN("Wide plains of grass stretch away from the river."));
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore", }),
	BSN("Rolling grasslands flow from the river east towards a " +
	    "black line on the horizon."));
    add_item( ({ "western bank", "west bank", "western shore",
	"west shore", }),
	BSN("A green sea of grass flows west from the river."));
    add_item( ({ "eastern horizon", "east horizon", "horizon",
	"black line", "line", }),
	BSN("The forest of Mirkwood forms a black line along the " +
	    "east horizon."));
    add_item( ({ "forest", "forest of mirkwood", "mirkwood" }),
	BSN("The forest of Mirkwood is barely visible " +
	    "on the east horizon."));
    add_item( ({ "west horizon", "western horizon", }),
	BSN("There is nothing but grass, as far as the eye can see."));
    add_item( ({ "rolling grassland", "rolling grasslands", "grassland", 
	"grasslands", "wide plain", "wide plains", "plain", "plains",
	"green sea", "sea", "green sea of grass", "sea of grass", }),
	BSN("Tall green grasses, flecked with gold, " +
	    "ripple like water in the wind."));
    add_item( ({ "tall green grass", "tall grass", "green grass",
	"tall green grasses", "tall grasses", "green grasses",
	"waist-high grass", "waist-high grasses", "grass", "grasses", }),
	BSN("The waist-high grasses toss and ripple in the " +
	    "slightest wind."));
} /* create_anduin_onwater */
