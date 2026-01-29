/*
 * /d/Gondor/lebennin/sroad/path1.c
 *
 * Copyright (C) May 21, 1998 by Ron Miller (Tyr)
 *
 * This is the first room of a trail that leads to the lens taken from 
 * the Pelargir lighthouse.
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/herbsearch";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    set_short("On a path");

    set_long(BSN("This appears to be the beginning of a trail that "+
        "follows the River Sirith as it makes its way toward the mighty "+
        "Anduin."));
 
    add_item(({"this","beginning","trail","here","area"}), BSN("A "+
        "well-trodden pathway has been worn into the grass here. It "+
        "follows the edge of the Sirith and makes its way through "+
        "the underbrush toward the south."));

    add_item(({"river","river sirith","sirith","edge","side",
        "opposite side","west"}), BSN("The River Sirith lies to the "+
        "west of the trail."));

    add_item(({"mighty anduin","anduin","confluence","rivers"}), 
        BSN("The confluence of the two rivers cannot be seen from "+
        "here."));

    add_item(({"pathway","path"}), BSN("The passage of people or"+
        "animals has crushed the grass into an obvious path "+
        "alongside the river here."));

    add_item(({"underbrush","bank"}), BSN("The bank of the river is "+
        "lined by a wide variety of shrubs typical of this area."));

    add_item(({"shrub","shrubs","trees","bushes","woody bushes",
        "variety"}), BSN("The short woody bushes here are actually "+
        "more like small trees."));

    add_item("south", BSN("The trail leaves here toward the south."));

    add_item(({"people","animals","traffic"}), BSN("No one who helped "+
        "create this trail appears to be nearby right now."));

    add_item(({"grass","blades","short blades","ground"}), BSN("The "+
        "short blades of grass here have been mashed flat by "+
        "frequent traffic through the area."));

    /* Adding herbs to this room */
    set_up_herbs( ({ (HERB_DIR+"blackberry"),
                     (HERB_DIR+"sage"),
                     (HERB_DIR+"raspberry"),
                  }),
                  ({ "grass","ground","bush","bushes","underbrush",}),
                  2);

    add_exit("sirithb", "north", 0, 4);
    add_exit("path2", "south", 0, 1);
} /* end create_gondor */
