/*
 * /d/Gondor/tharbad/trail/path2.c
 *
 * Copyright (C) May 28, 1998 by Ron Miller (Tyr)
 *
 * This is the second room of a trail that leads to the mirror taken from 
 * the Pelargir lighthouse.
 *
 * Revision history:
 *    5/19/99 - corsair npc added by Tyr
 *    6/17/99 - herbs added by Tyr
 *    6/28/99 - revised per Gnadnar's suggestions by Tyr
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/herbsearch";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* prototypes */
public void  create_gondor();
public void  reset_room();

object  *Corsair = allocate(1);

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
public void
create_gondor()
{
    set_short("On a path");

    set_long(BSN("This well-trodden pathway snakes along the edge of "+
        "the Greyflood and makes its way through the underbrush."));
 
    add_item( ({ "trail", "here", "area", "path" }) , BSN("The trail follows "+
        "the river's edge, disappearing in the underbrush."));

    add_item( ({ "river", "river greyflood", "greyflood", "edge", "side",
        "opposite side", "west", "river's edge", "rivers edge" }) ,
        BSN("The river Greyflood lies to the south of the trail."));

    add_item( ({ "pathway" }) , BSN("The passage of people or animals has "+
        "crushed the grass into an obvious path alongside the river "+
        "here."));

    add_item( ({ "underbrush", "bank" }) , BSN("The bank of the river is "+
        "lined by a wide variety of shrubs typical of this area."));

    add_item( ({ "shrub", "shrubs", "trees", "bushes", "woody bushes",
        "variety" }) , BSN("The short woody bushes here are actually "+
        "more like small trees."));

    add_item("southwest", BSN("The trail leaves here toward the "+
        "southwest."));

    add_item("east", BSN("The trail leaves here through the bushes "+
        "to the east."));

    add_item( ({ "people", "animals", "traffic" }) , BSN("No one who helped "+
        "create this trail appears to be nearby right now."));

    add_item( ({ "grass", "blades", "short blades", "ground" }) , BSN("The "+
        "short blades of grass here have been mashed flat by "+
        "frequent traffic through the area."));

    /* Adding herbs to this room */
    set_up_herbs( ({ (HERB_DIR+"lothore"),
                     (HERB_DIR+"redweed"),
                     (HERB_DIR+"suranie"),
                  }),
                  ({ "grass", "ground", "bush", "bushes", "underbrush",
                     "path", "pathway", }),
                  6);

    add_exit("path1", "east", 0, 1);
    add_exit("path3", "southwest", 0, 1);

    reset_room();
} /* end create_gondor () */

/*
 * Function name:    reset_room
 * Description:      add npc
 */
public void
reset_room()
{
    ::reset_room();

    /* add Corsair npc */
    clone_npcs(Corsair, (POROS_DIR + "npcs/corsair"), 0.0);
}   /* end reset_room */
