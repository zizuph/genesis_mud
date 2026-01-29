/*
 *  /d/Gondor/minas/n3crc6.c
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
    set_areaname("northern");
    set_streettype("narrow street");
    set_activity(0);
    set_wealth(2);

    add_exit(INNER_MINAS + "/n2crc6", "east", 0);
    add_exit(INNER_MINAS + "/w3crc6", "southwest", 0);

    /* This extraline is unique to each street room */

    set_extraline("To the south lies the wall of the Citadel. The "
        + "street continues southwest, lined by white and noble "
        + "buildings. The street also leads east, where "
        + "you hear the sounds of horses.");

    /* These items are similar in all streets on all levels */

    add_street_items();

    /* These items are unique to the specific streets on this circle */

    add_sixth_circle_items();

    /* These items are unique to this room */

    add_item(({"citadel wall", "citadel"}), "To the south, the great "
        + "wall of the Citadel "
        + "can be seen rising above the Sixth Circle. The tall White Tower "
        + "rises from within.\n");
    add_item(({"wall", "walls"}), "Which one? To the north is the sixth wall. "
        + "To the "
        + "south, the Citadel wall rises behind the buildings.\n");



    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    add_sixth_circle_tells();

    /* These tells are unique to this room */

    add_tell("The sounds of horses can be heard to the east.\n");
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

