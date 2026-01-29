/*
 * /d/Gondor/river/anduin/carrock2lorien/river09.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 230 miles south of the Carrock, northwest of Dol Guldur
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
	"230 miles south of the Carrock, northwest of Dol Guldur.\n");
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The Great River flows southwest through wide grasslands.");
    set_tod_landname("the vale of Anduin");	/* XXX */
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

    add_exit("river08", "northeast");
    set_distance("northeast", 25);
    add_exit("river10", "southwest");
    set_distance("southwest", 40);
    add_exit("riverbottom09", "down");
    /* no shore rooms for now */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The Great River is both wide and deep, and "+
	    "it rolls swiftly to the southeast."));
    add_item( ({ "land", "view", "vale", "inland", "river bank",
	"sides", "side", "river banks", "bank", "banks",
	"shore", "shores", }),
	BSN("Miles of open plains stretch away on either shore."));
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore", }),
	BSN("Rippling grasses extend east from the river. Far in "+
	    "the distance, they end at a black wall of trees."));
    add_item( ({ "wide grasslands", "grasslands", "wide grassland",
	"grassland", "plain", "plains" }),
	BSN("The plains, empty of all but grass, stretch for "+
	    "miles on either side of the river."));
    add_item( ({ "carpet", "rippling grass", "rippling grasses", "tall grass",
	"tall grasses", "grass", "grasses", }),
	BSN("Tall grasses roll away from the river like a "+
	    "carpet of green and gold."));
    add_item( ({ "edge", "western bank", "west bank", "western shore",
	"west shore",  }),
	BSN("Wide grasslands stretch west from the Great River "+
	    "as far as the eye can see."));
    add_item( ({ "black wall", "frowning wall", "black wall of trees",
	"frowning wall of trees", "wall", "wall of trees", "trees", }),
	BSN("Far to the east, the trees of Mirkwood form a wall "+
	    "beyond the grassland."));
    add_item( ({ "vast forest", "forest", "mirkwood" }),
	BSN("The vast forest of Mirkwood rises, dark and ominous, "+
	    "beyond the plains to the east."));

} /* create_anduin_onwater */
