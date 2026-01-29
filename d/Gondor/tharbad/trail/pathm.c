/*
 * Corsair room
 *
 * Raymundo, June 2020
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/herbsearch";
inherit "/d/Gondor/tharbad/trail/base_room";
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "defs.h"

/* prototypes */
public void  create_gondor();

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    FIX_EUID;
    set_short("In a clearing");

    set_long("You're standing in the middle of a clearing. It stretches "
        + "onward in every direction. However, this is not a natural "
        + "clearing; trees have been clear-cut to open up this space. "
        + "What trees are left provide privacy, making this a good place "
        + "to stage pirate raids on unsuspecting riverboats.\n");

    add_landscape();

    add_exit("pathl", "west");
    add_exit("patho", "southwest", 0, 0, 1);
    add_exit("pathq", "southeast", 0, 0, 1);
    add_exit("pathi", "northwest");
    add_exit("pathk", "northeast");
    add_exit("pathn", "east");
    add_exit("pathj", "north");
    add_exit("pathp", "south");

}   /* end create_gondor () */


