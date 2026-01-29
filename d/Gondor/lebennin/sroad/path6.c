/*
 * /d/Gondor/lebennin/sroad/path6.c
 *
 * Copyright (C) May 26, 1998 by Ron Miller (Tyr)
 *
 * This is the northeast corner of a clearing where the lens taken from 
 * the Pelargir lighthouse is hidden.
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

/* Function name:    create_gondor
 * Description:      create the basic room
 */
public void
create_gondor()
{
    set_short("The edge of a clearing");

    set_long(BSN("The north and east sides of the clearing are "+
        "completely blocked by the dense underbrush here. The center "+
        "of a small camp lies to the southwest."));

    add_item(({"edge","northern edge","clearing","small clearing",
        "here","space","side","sides"}), BSN("The underbrush has been "+
        "chopped back to provide enough space to set up a small camp "+
        "here."));

    add_item(({"remains","campfire","small campfire","pile","ashes",
        "wet ashes","firewood","burnt firewood"}), BSN("To the "+
        "southwest lies a pile of wet ashes and partially burnt "+
        "firewood."));

    add_item(({"someone","privateer","privateers","people"}),
        BSN("Luckily, the privateers who normally use this camp are "+
        "away at the moment."));

    add_item(({"camp","small camp","hideout","area"}), BSN("This camp "+
        "looks as if it may serve as some sort of hideout for the "+
        "Corsairs known to traffic the river near here."));

    add_item(({"southwest","center"}), BSN("The center of the camp "+
        "lies to the southwest."));

    add_item(({"corsair","corsairs"}), BSN("There are no Corsairs "+
        "in camp at the moment."));

    add_item(({"river","river sirith","sirith","west"}), BSN("The "+
        "River Sirith lies west of the clearing, beyond the underbrush "+
        "and trees."));

    add_item(({"north","north side","northern perimeter","perimeter",
        "direction"}), BSN("The underbrush which forms the northern "+
        "perimeter of this clearing is quite impenetrable."));

    add_item(({"east","east edge","east side","eastern edge"}),
        BSN("The eastern edge of the camp clearing is defined by the "+
        "close-spaced trees."));

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
    set_up_herbs( ({ (HERB_DIR+"athelas"),
                     (HERB_DIR+"lothore"),
                     (HERB_DIR+"attanar"),
                  }),
                  ({ "grass","ground","bush","bushes","underbrush",
                     "path","pathway",}),
                  3);

    add_exit("path5", "west", 0, 1);
    add_exit("path8", "southwest", 0, 1);
    add_exit("path9", "south", 0, 1);

    reset_room();
} /* end create_gondor () */

public void
reset_room()
{
    ::reset_room();

    /* add Corsair npc */
    set_alarm(4.0, 0.0,
        &clone_npcs(Corsair, (POROS_DIR + "npcs/corsair"), 10.0));
}   /* end reset_room */
