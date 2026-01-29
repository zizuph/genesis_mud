/*
 *  /d/Gondor/minas/n1crc6.c
 *
 *  Stable Street, Sixth Circle
 *
 *  Original code by Elessar (1992)
 *
 *  Last modified by Alto, 06 April 2001
 *      Added room tells and revised descriptions
 *
 */

#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";


#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define INNER_MINAS "/d/Gondor/minas"

public void
create_street()
{
    set_circle("Sixth");
    set_streetname("Stable Street");
    set_areaname("north-eastern");
    set_streettype("broad street");
    set_activity(0);
    set_wealth(2);

    add_exit(INNER_MINAS + "/n2crc6", "northwest", 0);
    add_exit(INNER_MINAS + "/e3crc6", "southeast", 0);

    /* This extraline is unique to each street room */

    set_extraline("To the southwest lies the wall of the Citadel. The "
        + "street narrows to the northwest.  The street continues to "
        + "the southeast.");

    /* These items are similar in all streets on all levels */

    add_street_items();

    /* These items are unique to the specific streets on this circle */

    add_sixth_circle_items();

    /* These items are unique to this room */

    add_item(({"citadel wall", "citadel"}), "To the southwest, the great "
        + "wall of the Citadel "
        + "can be seen rising above the Sixth Circle. The tall White Tower "
        + "rises from within.\n");
    add_item(({"wall", "walls"}), "Which one? To the northeast is the sixth wall. "
        + "To the "
        + "southwest, the Citadel wall rises behind the buildings.\n");



    set_tell_time(150);

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    add_sixth_circle_tells();

    /* These tells are unique to this room */

    add_tell("The sounds of horses can be heard to the northwest.\n");
    add_tell("A stablehand passes quickly down the street.\n");
    add_tell("The faint odor of manure wafts through the street.\n");

    reset_room();
}


/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

