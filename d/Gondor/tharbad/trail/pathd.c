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

/* prototypes */
public void  create_gondor();

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    set_short("A corsair encampment in a clearing");

    set_long("This encampment is larger than it looked at first, "
        + "likely because the trees have been cleared in such a "
        + "way as to provide privacy, but not much shade. "
        + "The encampment extends quite a ways to the west, "
        + "with signs of human activity abundant on the ground.\n");

    add_trash();
    add_landscape();

    add_exit("pathc", "west");
    add_exit("patha", "northwest");
    add_exit("pathf", "southwest", 0, 0, 1);
    add_exit("pathg", "southeast");

}   /* end create_gondor () */
