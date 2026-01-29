/*
 * /d/Gondor/tharbad/trail/path5.c
 *
 * Copyright (C) June 16, 1998 by Ron Miller (Tyr)
 *
 * Along the northwestern edge of a clearing where the mirror taken from 
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

int
wiz_check()
{
    if(TP->query_wiz_level())
    {
        write("\n\nThis area is not yet open to mortals.\n\n");
        return 0;
    }
    else
    {
        write("Trees have fallen across the path, making it impassable.\n");
        return 1;
    }
}

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    set_short("The edge of a clearing");

    set_long(BSN("A clearing opens in the easterly directions from "+
        "here."));

    add_item( ({ "clearing", "here", "expanse" }) , BSN("The underbrush gets "+
        "much thinner here, yielding to a grassy expanse toward the "+
        "south and east. It is the perfect setting for a well-hidden "+
        "bivouac."));

    add_item( ({ "setting", "bivouac", "hideout", "area", "camp" }) , 
        BSN("This camp looks as if it may serve as some sort of "+
        "hideout for the Corsairs known to traffic the river near "+
        "here."));

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
    set_up_herbs( ({ (HERB_DIR+"fennel"),
                     (HERB_DIR+"tyelka"),
                     (HERB_DIR+"ungolestel"),
                  }),
                  ({ "grass", "ground", "bush", "bushes", "underbrush",
                     "path", "pathway", }),
                  3);

    add_exit("path4", "northeast", 0, 1);
    add_exit("path6", "east", 0, 1);
    add_exit("path8", "southeast", 0, 1);
    add_exit("pathk", "west", 0, 0);
    add_exit("pathg", "northwest", 0, 0);
    add_exit("pathn", "southwest", 0, 0);
//    add_exit("pathg", "northwest", wiz_check, 0, 0);
//    add_exit("pathn", "southwest", wiz_check, 0, 0);
//    add_exit("pathk", "west", wiz_check, 0, 0);
}    /* end create_gondor () */
