/*
 *  /d/Gondor/minas/s2crc6.c
 *
 *  Isildur's Street, Sixth Circle
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
    set_streetname("Isildur's Street");
    set_areaname("southern");
    set_streettype("narrow street");
    set_activity(0);
    set_wealth(2);

    add_exit(INNER_MINAS + "/s1crc6", "east", 0, 0);
    add_exit(INNER_MINAS + "/s3crc6", "west", 0, 1);

    /* This extraline is unique to each street room */

    set_extraline("The steep face of Mount Mindolluin rises to the "
        + "west above the Sixth Wall. The street continues to the "
        + "west. Going east will take you toward the Sixth Gate. ");

    /* These items are similar in all streets on all levels */

    add_street_items();

    /* These items are unique to the specific streets on this circle */

    add_sixth_circle_items();

    /* These items are unique to this room */

    add_item(({"citadel wall", "citadel"}), "To the north, the great "
        + "wall of the Citadel "
        + "can be seen rising above the Sixth Circle. The tall White Tower "
        + "rises from within.\n");
    add_item(({"wall", "walls"}), "Which one? To the south is the sixth wall. "
        + "To the "
        + "north, the Citadel wall rises behind the buildings.\n");

    set_tell_time(150);


    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    add_sixth_circle_tells();

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

