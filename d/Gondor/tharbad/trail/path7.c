/*
 * /d/Gondor/tharbad/trail/path7.c
 *
 * Copyright (C) June 18, 1998 by Ron Miller (Tyr)
 *
 * Along the eastern edge of a clearing where the mirror taken from 
 * the Pelargir lighthouse is hidden.
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
    set_short("The edge of a clearing");

    set_long(BSN("The eastern edge of the clearing ends here."));

    add_item( ({ "edge", "clearing", "here", "expanse" }) , BSN("The "+
        "underbrush is thickest to the southeast. A grassy expanse "+
        "unfolds toward the westerly directions. This the perfect "+
        "setting for a well-hidden bivouac."));

    add_item( ({ "setting", "bivouac", "hideout", "area", "camp" }) , 
        BSN("This camp looks as if it may serve as some sort of "+
        "hideout for the Corsairs known to traffic the river near "+
        "here."));

    add_item( ({ "corsair", "corsairs" }) , BSN("There are no Corsairs "+
        "in camp at the moment."));

    add_item( ({ "river", "river greyflood", "greyflood" }) , BSN("The "+
        "river Greyflood lies far to the east of the clearing, beyond "+
        "the underbrush and trees."));

    add_item( ({ "east", "west", "direction", "directions",
        "westerly directions", "edges" }) , BSN("Past the edges of this "+
        "clearing, the underbrush is impenetrable."));

    add_item( ({ "underbrush", "southeast" }) , BSN("Upon closer "+
        "examination it is clear that someone has deliberately "+
        "rearranged these shrubs to conceal a small track leaving to "+
        "the southeast."));

    add_item( ({ "someone", "privateer", "privateers" }) , BSN("Luckily, "+
        "the privateers who normally use this camp are away at the "+
        "moment."));

    add_item( ({ "footprint", "footprints", "trail", "track" }) , BSN("Only "+
        "a few footprints, actually, the small trail has been "+
        "cleverly camouflaged with branches from the nearby shrubs."));

    add_item( ({ "shrub", "shrubs", "bushes", "woody bushes", "variety",
        "small trees" }) , BSN("The short woody bushes here are actually "+
        "more like small versions of the tall trees surrounding this "+
        "clearing."));

    add_item( ({ "tree", "trees", "tall trees" }) , BSN("Tall trees "+
        "completely surround this rather large clearing, totally "+
        "hiding it from prying eyes."));

    add_item( ({ "eye", "eyes", "prying eyes", "outsiders" }) , BSN("The thick "+
        "trees surrounding this clearing prevent spying by outsiders."));

    /* Adding herbs to this room */
    set_up_herbs( ({ (HERB_DIR+"angurth"),
                     (HERB_DIR+"thyme"),
                     (HERB_DIR+"redweed"),
                  }),
                  ({ "grass", "ground", "bush", "bushes", "underbrush",
                     "path", "pathway", }),
                  6);

    add_exit("path4", "northwest", 0, 1);
    add_exit("path6", "west", 0, 1);
    add_exit("path8", "southwest", 0, 1);
    add_exit("path9", "southeast", 0, 1, 1);
}    /* end create_gondor */
