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
    set_short("The south side of the clearing");

    set_long("Short trees, perhaps as a tall as a tall human, grow to the "
        + "east. Beyond them, you can hear the river, and occasionally "
        + "even frogs. West and north a man-made clearing opens up, "
        + "where corsairs have clear-cut the forest to make a private "
        + "encampment. During the day, shade is nearly impossible to "
        + "find and the sun is punishing.\n");

    add_landscape();

    add_exit("pathp", "west");
    add_exit("pathm", "northwest", 0, 0, 1);
    add_exit("pathn", "northeast");
    add_exit("pathr", "southwest");
}   /* end create_gondor () */


