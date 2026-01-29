/*
 *  /d/Gondor/minas/n2crc6.c
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

    add_exit(INNER_MINAS + "/n3crc6", "west", 0);
    add_exit(INNER_MINAS + "/n1crc6", "southeast", 0);

    /* This extraline is unique to each street room */

    set_extraline("To the south lies the wall of the Citadel. The "
        + "street continues west and southeast. To the north lie "
        + "the Royal Stables of Minas Tirith.");

    /* These items are similar in all streets on all levels */

    add_street_items();

    /* These items are unique to the specific streets on this circle */

    add_sixth_circle_items();

    /* These items are unique to this room */

    add_item(({"citadel wall", "citadel"}), "To the south, the great "
        + "wall of the Citadel "
        + "can be seen rising above the Sixth Circle. The tall White Tower "
        + "rises from within.\n");
    add_item(({"stable", "stables"}), "This large building is used by "
        + "the couriers of the Steward to house their mounts when they "
        + "are inside the Citadel. At the moment there seems to be an "
        + "an unusual amount of activity inside.\n");
    add_item(({"building", "buildings", "pavements", "halls", "doorway"}), 
        "Many great Men and kindreds "
        + "once dwelt here. Now many buildings are silent, and no footsteps "
        + "ring on their wide pavements, nor are voices heard in their "
        + "halls.  The building to the north encompasses the Royal Stables "
        + "of Minas Tirith.\n");
    add_item(({"wall", "walls"}), "Which one? To the north is the sixth wall. "
        + "To the "
        + "south, the Citadel wall rises behind the buildings.\n");


    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    add_sixth_circle_tells();

    /* These tells are unique to this room */

    add_tell("The sounds of horses can be heard to the north.\n");
    add_tell("A stablehand passes quickly down the street.\n");
    add_tell("The strong odor of manure wafts through the street.\n");
    add_tell("Horses whinny and champ inside the building to the north.\n");
    add_tell("Someone yells: Where are those special oats?\n");

    clone_object(INNER_MINAS +"/doors/stablegate_s1")->move(TO);


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

