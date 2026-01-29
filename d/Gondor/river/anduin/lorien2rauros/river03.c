/*
 * /d/Gondor/river/anduin/lorien2rauros/river03.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * ~40 miles south of the silverlode, about halfway between the
 * campsites for day 1 and day 2.
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
    add_prop(OBJ_S_WIZINFO,
	BSN("~40 miles downstream from the silverlode, about halfway " +
	    "between the campsites for day 1 and day 2."));
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The deep hurrying waters roll southeast past "
      + "tree-shrouded banks.");
    set_tod_landname("the Hill-lands");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir("southeast");
    set_upstreamdir("northwest");
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */

    add_exit("river02", "northwest");
    set_distance("northwest", 20);
    add_exit("river04", "southeast");
    set_distance("southeast", 20);
    add_exit("riverbottom03", "down");
    /* no shore rooms for now */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	"The Great River is deep, swift and silent.\n");
    add_item( ({ "hill-lands", "eastern shore", "east shore",
	"western shore", "west shore", "shore", "tree-shrouded shores",
	"shores", "eastern bank", "east bank", "western bank", "lands",
	"land", "west bank", "river bank", "river banks",
	"bank", "tree-shrouded banks", "banks" }),
	BSN("Trees grow close to the river along either shore, "+
	"obscuring all views of the lands beyond."));
    add_item( ({ "great trees", "tree", "trees", "forests", "forest",
	"woods" }),
	BSN("The trees thrust twisted thirsty roots down "
	  + "into the water."));
    add_item( ({ "root", "twisted thirsty roots", "twisted roots",
	"thirsty roots", "roots" }),
	BSN("Twisted and knotted with age, the roots thrust "
	  + "deep into the Anduin."));
} /* create_anduin_onwater */
