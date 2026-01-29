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
    set_short("The eastern edge of the clearing");

    set_long("To the east, the clearing narrows almost to a path, "
        + "and then opens back up into a clearing again. Moving that "
        + "direction, you would find yourself near the river. To "
        + "the west, you can see boxes stacked almost like a "
        + "wall. You can hear birds and frogs, but otherwise the "
        + "encampment is pretty quiet.\n");

    add_landscape();

    add_exit("pathj", "west");
    add_exit("pathm", "southwest");
    add_exit("pathn", "southeast");
    add_exit("pathf", "northwest");
    add_exit("pathg", "northeast");
    add_exit("path5", "east");

}   /* end create_gondor () */


