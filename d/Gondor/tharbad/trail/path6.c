/*
 * /d/Gondor/tharbad/trail/path6.c
 *
 * Copyright (C) June 16, 1998 by Ron Miller (Tyr)
 *
 * An open area near the center of a clearing where the mirror taken from 
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
    set_short("A forest clearing");

    set_long(BSN("The flattened spots in the grass and the campfire "+
        "preparations suggest that someone camps here in the center "+
        "of this clearing on a regular basis."));

    add_item( ({ "clearing", "here", "expanse", "grassy expanse", "center",
        "vicinity" }) , BSN("Totally surrounded by the distant "+
        "underbrush, this wide grassy expanse makes an excellent "+
        "place for a hidden encampment."));

    add_item( ({ "spots", "flattened spots", "grass", "areas", "large areas" }) ,
        BSN("There are large areas here where the grass was recently "+
        "compressed by something like large tents or sleeping mats."));

    add_item( ({ "firepit", "firewood", "kindling", "campfire",
        "preparations", "campfire preparations" }) , BSN("Firewood and "+
        "kindling is stacked beside a small pit here."));

    add_item( ({ "pit", "small pit" }) , BSN("The earth has been scooped "+
        "out in a rather crude attempt to form a pit to contain a "+
        "campfire."));

    add_item( ({ "earth", "ground" }) , BSN("There is nothing particularly "+
        "unusual about the ground here."));

    add_item( ({ "someone", "privateer", "privateers" }) , BSN("Luckily, "+
        "the privateers who normally use this camp are away at the "+
        "moment."));

    add_item( ({ "hiding place", "encampment", "hideout" }) , BSN("This "+
        "camp looks as if it may have recently served as some sort of "+
        "hideout for the Corsairs known to traffic the river not too "+
        "far from here."));

    add_item( ({ "tent", "tents", "mat", "mats", "sleeping mat",
        "sleeping mats" }) , BSN("Someone recently broke camp here and "+
        "no longer appears to be in the vicinity."));

    add_item( ({ "corsair", "corsairs" }) , BSN("There are no Corsairs "+
        "in camp at the moment."));

    add_item( ({ "river", "river greyflood", "greyflood" }) , BSN("The "+
        "river Greyflood lies far to the east of the clearing, beyond "+
        "the underbrush and trees."));

    add_item( ({ "west", "direction" }) , BSN("Past the edge of this "+
        "clearing, the underbrush is impenetrable."));

    add_item( ({ "underbrush" }) , BSN("This clearing is totally "+
        "surrounded by a wide variety of trees and shrubs typical "+
        "of this area."));

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
    set_up_herbs( ({ (HERB_DIR+"dill"),
                     (HERB_DIR+"catnip"),
                     (HERB_DIR+"carrot_wild"),
                  }),
                  ({ "grass", "ground", "bush", "bushes", "underbrush",
                     "path", "pathway", }),
                  3);

    add_exit("path4", "north", 0, 1);
    add_exit("path7", "east", 0, 1);
    add_exit("path5", "west", 0, 1);
    add_exit("path8", "south", 0, 1);
}   /* end create_gondor () */
