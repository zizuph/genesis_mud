/*
 * /d/Gondor/lebennin/sroad/path4.c
 *
 * Copyright (C) May 26, 1998 by Ron Miller (Tyr)
 *
 * This is the northwest corner of a clearing where the lens taken from 
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

object  *Corsair = allocate(2);

/* Function name:    create_gondor
 * Description:      create the basic room
 */
public void
create_gondor()
{
    set_short("The edge of a clearing");

    set_long(BSN("The path opens onto a clearing here. It appears "+
        "that someone has recently made camp to the southeast."));

    add_item(({"pathway","path","passage","trail"}), BSN("The passage "+
        "of people or animals has crushed the grass into an obvious "+
        "path toward the northwest."));

    add_item(({"clearing","here","space"}), BSN("The underbrush has "+
        "been chopped back to provide enough space to set up a small "+
        "camp here."));

    add_item(({"someone","privateer","privateers","people"}),
        BSN("Luckily, the privateers who normally use this camp are "+
        "away at the moment."));

    add_item(({"camp","small camp","hideout","area"}), BSN("This camp "+
        "looks as if it may serve as some sort of hideout for the "+
        "Corsairs known to traffic the river near here."));

    add_item(({"southeast","center"}), BSN("The center of the camp "+
       "lies to the southeast."));

    add_item("northwest", BSN("Despite crude attempts to hide it, the "+
       "path enters the bushes toward the northwest."));

    add_item(({"animals","animal","beast","beasts","beasts of burden"}),
       BSN("The Corsairs must house their beasts of burden elsewhere."));

    add_item(({"grass","blades","short blades","ground"}), BSN("The "+
        "short blades of grass here have been mashed flat by "+
        "frequent traffic through the area."));

    add_item(({"traffic","eyes","prying eyes"}), BSN("No one who helped "+
        "create this trail appears to be nearby right now."));

    add_item(({"corsair","corsairs"}), BSN("There are no Corsairs "+
        "in camp at the moment."));

    add_item(({"river","river sirith","sirith"}), BSN("The River Sirith "+
        "lies through the underbrush and trees to the west."));

    add_item(({"west","direction"}), BSN("The underbrush is "+
        "impenetrable in the direction of the Sirith."));

    add_item(({"underbrush"}), BSN("This clearing is totally "+
        "surrounded by a wide variety of trees and shrubs typical "+
        "of this area."));

    add_item(({"shrub","shrubs","bushes","woody bushes","variety",
        "small trees"}), BSN("The short woody bushes here are actually "+
        "more like small trees."));

    add_item(({"tree","trees","small trees"}), BSN("Tall trees "+
        "completely surround this small clearing, totally hiding it "+
        "from prying eyes."));

    add_item(({"eye","eyes","prying eyes","outsiders"}), BSN("The thick "+
        "trees surrounding this clearing prevent spying by outsiders."));


    /* Adding herbs to this room */
    set_up_herbs( ({ (HERB_DIR+"lothore"),
                     (HERB_DIR+"redweed"),
                     (HERB_DIR+"athelas"),
                  }),
                  ({ "grass","ground","bush","bushes","underbrush",
                     "path","pathway",}),
                  5);

    add_exit("path3", "northwest", 0, 1);
    add_exit("path5", "east", 0, 1);
    add_exit("path8", "southeast", 0, 1);
    add_exit("path7", "south", 0, 1);

    reset_room();
} /* end create_gondor () */

/*
 * Function name:    reset_room
 * Description:      add npc's
 */
public void
reset_room()
{
    ::reset_room();

    clone_npcs(Corsair, (POROS_DIR + "npcs/corsair"), 0.0);
} /* end reset_room */

