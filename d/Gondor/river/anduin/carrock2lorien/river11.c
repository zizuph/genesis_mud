/*
 * /d/Gondor/river/anduin/carrock2lorien/river11.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 300 miles south of the Carrock, 15 miles north of the Silverlode
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
	"300 miles south of the Carrock, 15 miles north of "+
	"the Silverlode.\n");
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The deep waters of the Great River flow from northeast "+
	 "to south between forested shores.");
    set_tod_landname("the Hill-lands");
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
    set_downstreamdir("south");
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */

    add_exit("river10", "northeast");
    set_distance("northeast", 30);
    add_exit((LORIEN_TO_RAUROS_DIR+"river01"), "south");
    set_distance("south", 15);
    add_exit("riverbottom11", "down");
    /* no shore rooms for now */


    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The waters are dark and swift-moving, and appear "+
	    "to be quite deep."));
    add_item( ({ "river bank", "river banks", "bank", "banks",
	"forested shore", "forested shores", "shore", "shores", }),
	BSN("Forest marches on either shore, enclosing "+
	    "the river between two walls of trees."));
    add_item( ({ "edge", "eastern bank", "east bank", "eastern shore",
	"east shore", }),
	BSN("Trees line the east bank of the river, growing "+
	    "right up to the edge of the water."));
    add_item( ({ "western bank", "west bank", "western shore",
	"west shore", }),
	BSN("All that can be seen to the west are trees."));
    add_item( ({ "forest", "forests", "wood", "woods", "tree", "wall",
	"wall of trees", "trees", "walls", "walls of trees", }),
	BSN("The trees grow thickly together, blocking all views "+
	    "inland."));
    add_item( ({ "land", "view", "hill-lands", "inland" }),
	BSN("All that can be seen of the Hill-lands are the trees "+
	    "lining either shore."));
} /* create_anduin_onwater */
