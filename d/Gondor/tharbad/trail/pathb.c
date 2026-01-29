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
    set_short("At the edge of the clearing");

    set_long("To the southeast, the clearing opens wide, creating a large "
        + "private space for an encampment. This seems to be the kind of "
        + "place where you can be safe from prying eyes and nosy neighbors. "
        + "Short trees surround the encampment, providing a little shade "
        + "from the otherwise blistering sun.\n");

    add_landscape();

    add_exit("pathc", "east");
    add_exit("patha", "northeast");
    add_exit("pathe", "southwest");
    add_exit("pathf", "southeast", 0, 0, 1);

}   /* end create_gondor () */
