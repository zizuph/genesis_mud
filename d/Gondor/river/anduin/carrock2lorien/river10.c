/*
 * /d/Gondor/river/anduin/carrock2lorien/river10.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 270 miles south of the Carrock, west of Dol Guldur
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
	"270 miles south of the Carrock, west of Dol Guldur.\n");
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"Trees line the west shore, and a wide plain of grass "+
	"unfolds to the east. The Anduin rolls southwest, "+
	"swift and silent.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* set up water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("northeast");
    set_downstreamdir("southwest");
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */

    add_exit("river09", "northeast");
    set_distance("northeast", 40);
    add_exit("river11", "southwest");
    set_distance("southwest", 30);
    add_exit("riverbottom10", "down");
    /* no shore rooms for now */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The river is quite wide and though its current is silent "+
	    "and smooth, it is nonetheless swift."));
    add_item( ({ "land", "view", "vale", "inland", "river bank",
	"river banks", "bank", "banks", "shore", "shores", }),
	BSN("The east shore is open grassland, while the west shore "+
	    "is heavily wooded."));
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore", }),
	BSN("Wide grassland runs east from the river towards "+
	    "a black wall of trees in the distance."));
    add_item( ({ "tall grass", "tall grasses", "grass", "grasses",
	"wide grassland", "grassland" }),
	BSN("Tall grasses stretch smoothly away east towards a "+
	    "wall of trees."));
    add_item( ({ "edge", "western bank", "west bank", "western shore",
	"west shore",  }),
	BSN("Forest grows to the very edge of the west shore, "+
	    "blocking all view inland."));
    add_item( ({ "forest", "forests", "wood", "woods", "tree",
	"trees", }),
	BSN("Trees grow thickly on the west shore, advancing "+
	    "to the edge of the river. In the distance to "+
	    "the east, more trees form a black wall "+
	    "beyond the grasslands."));
    add_item( ({ "black wall", "frowning wall", "black wall of trees",
	"frowning wall of trees", "wall", "wall of trees", }),
	BSN("Mirkwood waits like a black and "+
	    "frowning wall beyond the grassland."));
    add_item( ({ "mirkwood" }),
	BSN("The vast forest of Mirkwood rises, dark and ominous, "+
	    "perhaps twenty leagues to the east."));
} /* create_anduin_onwater */
