/*
 * /d/Gondor/lebennin/sroad/path7.c
 *
 * Copyright (C) May 26, 1998 by Ron Miller (Tyr)
 *
 * This is the western edge of a clearing where the lens taken from 
 * the Pelargir lighthouse is hidden.
 *
 * Revision history:
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

/* Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    set_short("The edge of a clearing");

    set_long(BSN("This is the western edge of a small clearing. "+
        "The remains of a small campfire to the east suggest "+
        "that someone recently camped here."));

 
    add_item(({"edge","western edge","clearing","small clearing",
        "here","space"}), BSN("The underbrush has been chopped back to "+
        "provide enough space to set up a small camp here."));

    add_item(({"remains","campfire","small campfire","pile","ashes",
        "wet ashes","firewood","burnt firewood"}), BSN("To the "+
        "east lies a pile of wet ashes and partially burnt firewood."));

    add_item(({"someone","privateer","privateers","people"}),
        BSN("Luckily, the privateers who normally use this camp are "+
        "away at the moment."));

    add_item(({"camp","small camp","hideout","area"}), BSN("This camp "+
        "looks as if it may serve as some sort of hideout for the "+
        "Corsairs known to traffic the river near here."));

    add_item(({"south","center"}), BSN("The center of the camp lies to "+
        "the east."));

    add_item(({"corsair","corsairs"}), BSN("There are no Corsairs "+
        "in camp at the moment."));

    add_item(({"river","river sirith","sirith"}), BSN("The River Sirith "+
        "lies west of the clearing, beyond the underbrush and trees."));

    add_item(({"west","direction"}), BSN("Past the edge of this "+
        "clearing, the underbrush is impenetrable."));

    add_item(({"underbrush"}), BSN("This clearing is totally "+
        "surrounded by a wide variety of trees and shrubs typical "+
        "of this area."));

    add_item(({"shrub","shrubs","bushes","woody bushes","variety",
        "small trees"}), BSN("The short woody bushes here are actually "+
        "more like small versions of the tall trees surrounding this "+
        "clearing."));

    add_item(({"tree","trees","tall trees"}), BSN("Tall trees "+
        "completely surround this small clearing, totally hiding it "+
        "from prying eyes."));

    add_item(({"eye","eyes","prying eyes","outsiders"}), BSN("The thick "+
        "trees surrounding this clearing prevent spying by outsiders."));

    /* Adding herbs to this room */
    set_up_herbs( ({ (HERB_DIR+"holly"),
                     (HERB_DIR+"ginger"),
                     (HERB_DIR+"alfirin"),
                  }),
                  ({ "grass","ground","bush","bushes","underbrush",
                     "path","pathway",}),
                  4);

    add_exit("path4", "north", 0, 1);
    add_exit("path5", "northeast", 0, 1);
    add_exit("path8", "east", 0, 1);
    add_exit("path11","southeast", 0, 1);
    add_exit("path10", "south", 0, 1);
} /* end create_gondor */
