/*
 * /d/Gondor/lebennin/sroad/path2.c
 *
 * Copyright (C) May 21, 1998 by Ron Miller (Tyr)
 *
 * This is the second room of a trail that leads to the lens taken from 
 * the Pelargir lighthouse.
 *
 * Revision history:
 *    5/19/99 - corsair npc added by Tyr
 *    6/17/99 - herbs added by Tyr
 *    6/28/99 - revised per Gnadnar's suggestions by Tyr
 *    3/01/07 - Removed BSN and fixed typo
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/herbsearch";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* prototypes */
public void  create_gondor();
public void  reset_room();

object    *Corsair = allocate(1);

/* Function name:    create_gondor
 * Description:      create the basic room
 */
public void
create_gondor()
{
    FIX_EUID;

    set_short("On a path");

    set_long("The trail follows the river's edge, disappearing "+
        "in the underbrush to the north and southwest.\n");
 
    add_item(({"trail","here","area"}), "A well-trodden pathway "+
        "has been worn into the grass here. It snakes along the "+
        "edge of the Sirith and makes its way through the "+
        "underbrush toward the southwest.\n");

    add_item(({"river","river sirith","sirith","edge","side",
        "opposite side","west","river's edge","rivers edge"}),
        "The River Sirith lies to the west of the trail.\n");

    add_item(({"pathway","path"}), "The passage of people or "+
        "animals has crushed the grass into an obvious path "+
        "alongside the river here.\n");

    add_item(({"underbrush","bank"}), "The bank of the river is "+
        "lined by a wide variety of shrubs typical of this area.\n");

    add_item(({"shrub","shrubs","trees","bushes","woody bushes",
        "variety"}), "The short woody bushes here are actually "+
        "more like small trees.\n");

    add_item("southwest", "The trail leaves here toward the "+
        "southwest.\n");

    add_item("north", "The trail leaves here through the bushes "+
        "to the north.\n");

    add_item(({"people","animals","traffic"}), "No one who helped "+
        "create this trail appears to be nearby right now.\n");

    add_item(({"grass","blades","short blades","ground"}), "The "+
        "short blades of grass here have been mashed flat by "+
        "frequent traffic through the area.\n");

    /* Adding herbs to this room */
    set_up_herbs( ({ (HERB_DIR+"bpotato"),
                     (HERB_DIR+"attanar"),
                     (HERB_DIR+"sumac"),
                  }),
                  ({ "grass","ground","bush","bushes","underbrush",
                     "path","pathway",}),
                  2);

    add_exit("path1", "north", 0, 2);
    add_exit("path3", "southwest", 0, 1);

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

    /* add Corsair npc */
    set_alarm(4.0, 0.0,
        &clone_npcs(Corsair, (POROS_DIR + "npcs/corsair"), 10.0));
}   /* end reset_room */
