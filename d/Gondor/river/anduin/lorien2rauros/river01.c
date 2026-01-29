/*
 * /d/Gondor/river/anduin/lorien2rauros/river01.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * The beginning of the section of Anduin that runs from the intersection
 * with the Silverlode to Nen Hithoel.
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
public void		create_anduin_onwater();


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO, "At the intersection with the Silverlode.\n");
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The Great River rolls from north to southeast, its waters deep and "
      + "dark. From the west, the Silverlode flows glittering "
      + "to join the Anduin.");
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
    set_upstreamdir("north");
    set_downstreamdir("southeast");
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */

    add_exit((CARROCK_TO_LORIEN_DIR+"river11"), "north");
    set_distance("north", 15);
    add_exit("river02", "southeast");
    set_distance("southeast", 20);
    add_exit("riverbottom01", "down");
    /* no shore rooms for now */

    /* msgs that talk about the currents, waters, etc  must make
     * sense for both swim and row ...
     */
    set_no_exit_msg( ({ "west", "northwest", "southwest" }),
	BSN("The waters of the Silverlode rise in a swelling crest and "+
	    "sweep you back into the Anduin."));

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	"The Anduin is swift, and its waters deep.\n");
    add_item( ({ "celebrant", "river celebrant", "celebrant river",
	"river silverlode", "silverlode river", "silverlode" }),
	BSN("The rippling waters of the Silverlode flow from the west, "
	  + "past a narrow tongue of lawn, to join the Great River.") );
    add_item( ({ "river bank", "river banks", "bank", "banks",
	"shore", "shores" }),
	BSN("The western shore is a smooth lawn. To the east, "
	  + "only woods are visible.") );
    add_item( ({ "western bank", "west bank", "western shore",
	"west shore", "smooth lawn", "narrow tongue", "lawn", "tongue" }),
	BSN("A smooth lawn, studded with golden flowers, extends "
	  + "in a narrow tongue between the Anduin and the Silverlode.") );
    add_item( ({ "elanor", "golden flower", "flower", "golden flowers",
	"flowers" }),
	BSN("The small star-shaped flowers are as gold as the sun.") );
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore", "hill-lands", "land", "tree", "trees",
	"forests", "forest", "woods" }),
	BSN("Trees crowd the east shore, blocking any glimpse of the "
      + "land beyond.") );
} /* create_anduin_onwater */
