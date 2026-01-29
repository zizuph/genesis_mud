/*
 * /d/Gondor/tharbad/trail/path1.c
 *
 * Copyright (C) May 28, 1998 by Ron Miller (Tyr)
 *
 * This is the first room of a trail that leads to the mirror taken from 
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

    set_long(BSN("A well-trodden pathway has been worn into the "+
        "grass here. It follows an arm of the river Greyflood and "+
        "makes its way through the underbrush toward the west."));

    add_item( ({ "this", "beginning", "trail", "here", "area" }) , BSN("This "+
        "appears to be the beginning of a trail that makes its way "+
        "along the bank of the Greyflood."));

    add_item( ({ "river", "river greyflood", "greyflood", "edge",
        "side", "arm", "opposite side", "south", "tributary" }) , 
        BSN("The great river Greyflood, lies to the south of the "+
        "trail."));

    add_item( ({ "pathway", "path" }) , BSN("The grass here has been "+
        "trampled by people or animals, leaving an obvious path "+
        "alongside the river here."));

    add_item( ({ "underbrush", "bank" }) , BSN("The bank of the river is "+
        "lined by a wide variety of shrubs typical of this area."));

    add_item( ({ "shrub", "shrubs", "trees", "bushes", "woody bushes",
        "variety" }) , BSN("The short woody bushes here are actually "+
        "more like small trees."));

    add_item("west", BSN("The trail leaves here toward the west."));

    add_item( ({ "people", "animals", "traffic" }) , BSN("No one who helped "+
        "create this trail appears to be nearby right now."));

    add_item( ({ "grass", "blades", "short blades", "ground" }) , BSN("The "+
        "short blades of grass here have been mashed flat by "+
        "frequent traffic through the area."));

    /* Adding herbs to this room */

    set_up_herbs( ({ (HERB_DIR+"holly"),
                     (HERB_DIR+"blueberry"),
                     (HERB_DIR+"laurel"),
                  }),
                  ({ "grass", "ground", "bush", "bushes", "underbrush",
                     "path", "pathway", }),
                  3);

    add_exit((THARBAD_DIR + "ford/f04"), "northeast", 0, 1);
    add_exit("path2", "west", 0, 1);

} /* end create gondor */
