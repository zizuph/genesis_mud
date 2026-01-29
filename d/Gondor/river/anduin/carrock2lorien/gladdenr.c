/*
 * /d/Gondor/river/anduin/carrock2lorien/gladdenr.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * Gladder River just upstream of its merge with the Anduin
 *
 */

#pragma strict_types

/*xxxxxxxxxxxxxxxxxxxxxxxxxxx a 72-char line xxxxxxxxxxxxxxxxxxxxxxxxx*/

/* yes, it says "anduin" -- but it works for this one gladden room too */
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
	"1 miles west of the junction of Gladden and Anduin\n");
    set_short("on the Gladden River");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The Gladden River flows eastward between fields of tall " +
	"gold-flecked grasses.");
    set_tod_landname("the Gladden Fields");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* set up water stuff */
    set_watertype("river");
    set_watername("Gladden River");
    set_waterrefs( ({ "waters", "water", "river", "gladden",
	"river gladden", "gladden river", "river ninglor",
	"ninglor river", "ninglor", }) );
    set_upstreamdir("west");
    set_downstreamdir("east");
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */

    add_exit("river06", "east");
    set_distance("east", 1);
    add_exit("gladdenrbottom", "down");
    /* no shore rooms for now */

    set_no_exit_msg("west",
	BSN("The current is swift, and you can make no headway."));

    add_item( ({ "flow", "waters", "water", "river gladden",
	"gladden river", "gladden", "river" }),
	BSN("The Gladden River flows swiftly east, its waters deep " +
	    "and silent."));
    add_item( ({ "anduin", "river anduin", "anduin river",
	"great river", }),
	BSN("Just visible in the distance to the east, the Great " +
	    "River stretches north and south like a silver ribbon " +
	    "across the plains."));
    add_item( ({ "silver ribbon", "ribbon" }),
	BSN("The silver grey waters of the Great River flow " +
	    "down the vale of Anduin like a ribbon."));
    add_item( ({ "land", "view", "vale", "inland", "river bank",
	"river banks", "bank", "banks", "shore", "shores",
	"gladden fields", "fields", "field", "grassland", "grasslands",
	"broad plain", "broad plains", "plain", "plains", }),
	BSN("Broad plains of green and gold grass stretch away " +
	    "on either side of the river."));
    add_item( ({ "northern bank", "north bank", "northern shore",
	"north shore", }),
	BSN("Grasses, waving gently in the slightest breeze, stretch " +
	    "north as far as one can see."));
    add_item( ({ "southern bank", "south bank", "southern shore",
	"south shore", }),
	BSN("Tall grasses cover the south shore, covering the " +
	    "land like a soft blanket."));
    add_item( ({ "tall grass", "green grass", "tall grasses",
	"green grasses", "gold grass", "gold grasses",
	"gold-flecked grass", "gold-flecked grasses",
	"grass", "grasses", }),
	BSN("Green grasses, tipped with gold, cloak both shores."));
    add_item( ({ "soft blanket", "great blanket", "blanket", }),
	BSN("The grasses grow so thickly together, it is as if " +
	    "a great blanket covered the plains."));
} /* create_anduin_onwater */
