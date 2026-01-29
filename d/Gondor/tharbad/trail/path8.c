/*
 * /d/Gondor/tharbad/trail/path8.c
 *
 * Copyright (C) June 24, 1998 by Ron Miller (Tyr)
 *
 * This is the southern edge of a clearing where the mirror taken from 
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

    set_long(BSN("There are indications that someone may have "+
        "recently camped in the clearing to the north of here. "+
        "A small path dives back into the underbrush to the "+
        "southeast."));

    add_item( ({ "path", "trail" }) , BSN("Someone has passed this way "+
        "often enough to create a trail through the underbrush here."));

    add_item( ({ "looks", "indications", "north" }) , BSN("Several of the "+
        "smaller trees have been chopped into firewood and stacked "+
        "beside a small firepit a little farther to the north."));
 
    add_item( ({ "clearing", "here", "expanse" }) , BSN("The underbrush gets "+
        "much thinner here, yielding to a grassy expanse toward the "+
        "north. It is the perfect setting for a well-hidden bivouac."));

    add_item( ({ "firepit", "firewood", "kindling", "south" }) , BSN("Firewood "+
        "and kindling is stacked beside a small pit farther to the "+
        "north in the clearing."));

    add_item( ({ "someone", "privateer", "privateers", "people" }) ,
        BSN("Luckily, the privateers who normally use this camp are "+
        "away at the moment."));

    add_item( ({ "setting", "bivouac", "hideout", "area", "camp" }) ,
        BSN("This camp looks as if it may serve as some sort of "+
        "hideout for the Corsairs known to traffic the river near "+
        "here."));

    add_item( ({ "corsair", "corsairs" }) , BSN("There are no Corsairs "+
        "in camp at the moment."));

    add_item( ({ "river", "river greyflood", "greyflood" }) , BSN("The river "+
        "greyflood lies east of the clearing, beyond the underbrush "+
        "and trees."));

    add_item( ({ "east", "direction" }) , BSN("Past the edge of this "+
        "clearing, the underbrush is impenetrable."));

    add_item( ({ "underbrush" }) , BSN("This clearing is totally "+
        "surrounded by a wide variety of trees and shrubs typical "+
        "of this area."));

    add_item( ({ "shrub", "shrubs", "bushes", "woody bushes", "variety",
        "small trees" }) , BSN("The short woody bushes here are actually "+
        "more like small versions of the tall trees surrounding this "+
        "clearing."));

    add_item( ({ "tree", "trees", "tall trees" }) , BSN("Tall trees "+
        "completely surround this small clearing, totally hiding it "+
        "from prying eyes."));

    add_item( ({ "eye", "eyes", "prying eyes", "outsiders" }) , BSN("The thick "+
        "trees surrounding this clearing prevent spying by outsiders."));

    /* Adding herbs to this room */
    set_up_herbs( ({ (HERB_DIR+"attanar"),
                     (HERB_DIR+"holly"),
                     (HERB_DIR+"handasse"),
                  }),
                  ({ "grass", "ground", "bush", "bushes", "underbrush",
                     "path", "pathway", }),
                  4);

    add_exit("path5", "northwest", 0, 1);
    add_exit("path6", "north", 0, 1);
    add_exit("path7", "northeast", 0, 1);
    add_exit("path10", "southeast", 0, 1);
}   /* end create_gondor */
