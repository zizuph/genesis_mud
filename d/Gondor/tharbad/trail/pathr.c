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
    set_short("The end of the encampment");

    set_long("The encampment ends here. Trees surround you on most "
        + "sides, providing privacy but little shade. To the north, "
        + "a wide clearing extends a very long way, and sounds of "
        + "people interacting with each other echo through it. "
        + "Sometimes you can hear birds or frogs, when the corsairs "
        + "are quiet, and still other times the whole clearing becomes "
        + "unnaturally silent, as if all living things here collectively "
        + "held their breath, fearing discovery.\n");

    add_landscape();

    add_exit("patho", "northwest");
    add_exit("pathq", "northeast");
    add_exit("pathp", "north");
}   /* end create_gondor () */
