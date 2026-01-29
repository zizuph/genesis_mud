/*
 * /d/Gondor/river/anduin/carrock2lorien/river06.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 100 miles south of the Carrock
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
    add_prop(OBJ_S_WIZINFO, "100 miles south of the Carrock\n");
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The Great River rolls south past wide fields of grass.");
    set_tod_landname("the vale of Anduin");
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

    add_exit("river05", "north");
    set_distance("north", 25);
    add_exit("gladdenm", "south");
    set_distance("south", 35);
    add_exit("riverbottom06", "down");
    /* no shore rooms for now */

    add_item( ({ "flow", "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The waters are deep and swift. They flow south " +
	    "down the vale of Anduin."));
    add_item( ({ "terrain", "land", "view", "vale", "inland", "river bank",
	"river banks", "bank", "banks", "shore", "shores",
	"gladden fields", "fields", "field", "grassland", "grasslands",
	"broad plain", "broad plains", "plain", "plains", }),
	BSN("Tall green grasses cloak both shores, hiding all " +
	    "details of the terrain."));
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore", }),
	BSN("Save for a dark line on the horizon, nothing but " +
	    "grass is visible."));
    add_item( ({ "west horizon", "western horizon", "side",
	"western bank", "west bank", "western shore", "west shore", }),
	BSN("The grasses stretch west, seemingly forever."));
    add_item( ({ "eastern horizon", "east horizon", "horizon",
	"black line", "line", }),
	BSN("The forest of Mirkwood is just a black line, far " +
	    "to the east."));
    add_item( ({ "smudge", "forest", "forest of mirkwood", "mirkwood" }),
	BSN("No details are visible -- the forest is just a smudge " +
	    "on the horizon."));
    add_item( ({ "tall green grass", "tall grass", "green grass",
	"tall green grasses", "tall grasses", "green grasses",
	"grass", "grasses", }),
	BSN("Luxuriant grasses grow thickly on either shore."));
} /* create_anduin_onwater */
