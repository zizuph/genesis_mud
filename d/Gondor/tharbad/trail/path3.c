/*
 * /d/Gondor/tharbad/trail/path3.c
 *
 * Copyright (C) May 28, 1998 by Ron Miller (Tyr)
 *
 * This is the third room of a trail that leads to the mirror taken from 
 * the Pelargir lighthouse.
 *
 * Revision history:
 *    6/17/99 - herbs added by Tyr
 *    6/28/99 - Revised per Gnadnar's suggestions by Tyr
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/herbsearch";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* prototypes */
public void  create_gondor();

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    set_short("On a path");

    set_long(BSN("The path gets narrower and moves slightly away from "+
        "the river's edge here. It appears to open onto a clearing "+
        "toward the southwest."));
 
    add_item( ({ "trail", "here", "area", "path", "point" }) , BSN("A thin "+
        "layer of underbrush separates the trail from the river at "+
        "this point."));

    add_item( ({ "river", "river greyflood", "greyflood", "edge", "side",
        "opposite side", "east", "river's edge", "rivers edge" }) ,
        BSN("The river Greyflood lies to the east of the trail, "+
        "through the underbrush."));

    add_item( ({ "pathway", "path", "trail" }) , BSN("The passage of people "+
        "or animals has crushed the grass into an obvious path "+
        "alongside the river here."));

    add_item( ({ "underbrush", "bank" }) , BSN("The bank of the river is "+
        "lined by a wide variety of shrubs typical of this area."));

    add_item( ({ "shrub", "shrubs", "trees", "bushes", "woody bushes",
        "variety" }) , BSN("The short woody bushes here are actually "+
        "more like small trees."));

    add_item("southwest", BSN("The trail leaves here toward the "+
        "southwest."));

    add_item("northeast", BSN("The trail leaves here through the "+
        "bushes to the northeast."));

    add_item( ({ "people", "animals", "traffic" }) , BSN("No one who helped "+
        "create this trail appears to be nearby right now."));

    add_item( ({ "grass", "blades", "short blades", "ground" }) , BSN("The "+
        "short blades of grass here have been mashed flat by "+
        "frequent traffic through the area."));

    set_up_herbs( ({ (HERB_DIR+"laurel"),
                     (HERB_DIR+"lissuin"),
                     (HERB_DIR+"astaldo"),
                  }),
                  ({ "grass", "ground", "bush", "bushes", "underbrush",
                     "path", "pathway", }),
                  4);

    add_exit("path2", "northeast", 0, 1);
    add_exit("path4", "southwest", 0, 1);
} /* end create gondor */
