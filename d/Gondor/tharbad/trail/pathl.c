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
    set_short("The west side of the encampment");

    set_long("Short trees block passage to the west. To the east, "
        + "however, is a large open clearing, which functions as an "
        + "encampment for corsairs. From here, they are able to raid "
        + "riverboats on the river to the east, enriching themselves. "
        + "The ground is mostly dirt, with a few patches of grass here "
        + "and there, and shade is hard to come by during the heat of "
        + "the day.\n");

    add_landscape();

    add_exit("patho", "southeast");
    add_exit("pathh", "northwest");
    add_exit("pathi", "northeast");
    add_exit("pathm", "east");
}   /* end create_gondor () */


