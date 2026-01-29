/*
 * /d/Gondor/river/anduin/lorien2rauros/river04.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * ~60 miles south of the silverlode, at the campsite for day 2.
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
	BSN("60 miles downstream from the silverlode, at the "+
	    "campsite for day 2."));
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The waters are deep, and flow swiftly southeast "
      + "past the forests on either shore.");
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

    add_exit("river03", "northwest");
    set_distance("northwest", 20);
    add_exit("river05", "southeast");
    set_distance("southeast", 25);
    add_exit("riverbottom04", "down");
    add_exit("beach04w", "west");

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The waters of the Anudin flow southeast past the "
      + "over-shadowing trees."));
    add_item( ({ "hill-lands", "shore", "tree-shrouded shores",
	"shores", "river bank", "river banks",
	"bank", "tree-shrouded banks", "banks" }),
	BSN("Trees shroud both banks of the Great River, hiding "+
	"what might lie inland. On the west shore, a giant tree "+
	"thrusts great roots into the water."));
    add_item( ({ "eastern shore", "east shore", "eastern bank",
	"east bank", }),
	BSN("The trees along the eastern bank of the river appear "+
	    "impenetrable."));
    add_item( ({ "western shore", "west shore", "western bank",
	"edge", "west bank", }),
	BSN("Trees grow thickly along the west bank, but there "+
	    "is a narrow patch of sand between the roots of a "+
	    "particularly large tree, right at the edge of "+
	    "the river."));
    add_item( ({ "great roots", "root", "great root", "roots",
	"flat sandy area", "sandy area", "area", "open patch",
	"open patch of sand", "narrow patch", "narrow patch of sand",
	"breach", "patch", "patch of sand", "sand", }),
	BSN("Roots as thick as your wrist enclose a sandy opening "+
	    "at the very edge of the water."));
    add_item( ({ "sandy opening", "opening", "breach" }),
	BSN("The flat, sandy area is the only breach in the wall "+
	    "of trees lining the west shore."));
    add_item( ({ "wall of trees", "wall" }),
	BSN("Save for the open patch of sand, the trees appear "+
	    "impenetrable."));
    add_item( ({ "particularly large tree", "large tree", "giant tree" }),
	BSN("The tree is a giant. Its roots spread over the "+
	   "bank and down into the water, enclosing a narrow "+
	   "patch of sand."));
    add_item( ({ "tree", "trees", "forests", "forest", "woods" }),
	BSN("Trees line both shores, leaning far out over the water. "+
	    "A particularly large tree on the west shore shoulders "+
	    "thrusts great roots into the river."));
} /* create_anduin_onwater */
