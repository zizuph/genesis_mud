/*
 * /d/Gondor/river/anduin/carrock2lorien/gladdenm.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 135 miles south of the Carrock, at the mouth of the 
 * Gladden River
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
	"135 miles south of the Carrock, at the mouth of " +
	"the Gladden River.\n");
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The Gladden River flows from the west to join the Anduin, " +
	"and the mingled waters of the two rivers roll south between " +
	"broad plains of grass.");
    set_tod_landname("the Gladden Fields");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* set up water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river",
	"anduin", "river anduin", "anduin river" }) );
    set_upstreamdir( ({ "north", "west" }) );
    set_downstreamdir("south");
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */

    add_exit("river06", "north");
    set_distance("north", 35);
    add_exit("gladdenr", "west");
    set_distance("south", 1);
    add_exit("river07", "south");
    set_distance("south", 40);
    add_exit("gladdenmbottom", "down");
    /* no shore rooms for now */

    add_item( ({ "flow", "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The waters of the Anduin, deep and swift, flow " +
	    "south past the Gladden Fields."));
    add_item( ({ "river ninglor", "ninglor river", "ninglor",
    	"river gladden", "gladden river", "gladden", }),
	BSN("The Gladden River flows from the west to join " +
	    "the Anduin. The waters of the two rivers merge " +
	    "smoothly in their course south."));
    add_item( ({ "land", "view", "vale", "inland", "river bank",
	"river banks", "bank", "banks", "shore", "shores",
	"gladden fields", "fields", "field", "grassland", "grasslands",
	"broad plain", "broad plains", "plain", "plains", }),
	BSN("Fields of tall grass unfold on either shore " +
	    "like a great blanket of green and gold wool."));
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore", }),
	BSN("Tall grasses cover the land to the east, extending " +
	    "all the way to a black line on the horizon."));
    add_item( ({ "west horizon", "western horizon", "side",
	"western bank", "west bank", "western shore", "west shore", }),
	BSN("Green and gold grasses extend west along either side " +
	    "of the Gladden River."));
    add_item( ({ "eastern horizon", "east horizon", "horizon",
	"black line", "line", }),
	BSN("A black line far on the east horizon marks the " +
	    "beginning of the forest of Mirkwood."));
    add_item( ({ "forest", "forest of mirkwood", "mirkwood" }),
	BSN("All that can be seen from here is a black line, just " +
	    "visible in the distance to the east."));
    add_item( ({ "tall green grass", "tall grass", "green grass",
	"tall green grasses", "tall grasses", "green grasses",
	"waist-high grass", "waist-high grasses", "grass", "grasses", }),
	BSN("Waist-high green grasses, tipped with gold, cover " +
	    "the plains."));
    add_item( ({ "soft-textured blanket", "great blanket", "blanket", }),
	BSN("The grasses grow so thickly together, it is as if " +
	    "a soft-textured blanket covered the plains."));
} /* create_anduin_onwater */
