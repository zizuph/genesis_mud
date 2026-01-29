/*
 *  /d/Gondor/minas/gate6.c
 *
 *  Inside 6th Gate
 *
 *  Original code by Elessar (1992)
 *
 *  Subsequent modifications by Olorin (29-Jan-1997)
 *      Changed inheritance
 *  Last modified by Alto, 06 April 2001
 *      Added room tells and revised descriptions
 *
 */

#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";
inherit "/d/Gondor/minas/lib/std_gate.c";


#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define INNER_MINAS "/d/Gondor/minas"

public void
create_street()
{
    set_circle("Sixth");
    set_streetname("Main Street");
    set_areaname("south-eastern");
    set_streettype("broad street");
    set_activity(0);
    set_wealth(2);

    add_exit(INNER_MINAS + "/e1crc6", "northeast",               0, 1);
    add_exit("/d/Gondor/minas/s1crc5", "southeast", "@@pass_gate@@", 1);
    add_exit(INNER_MINAS + "/s1crc6", "southwest",               0, 1);


    /* This extraline is unique to each street room */

    set_extraline("To the southeast lies the Sixth Gate, "
        + "which leads out to the Fifth Circle beyond the wall. The "
        + "Main Street continues northeast, and a narrower street to "
        + "the southwest.");


    /* These items are similar in all streets on all levels */

    add_street_items();

    /* These items are unique to the specific streets on this circle */

    add_sixth_circle_items();

    /* These items are unique to this room */

    add_item(({"wall", "walls"}), "Which one? Before you is the sixth wall. "
        + "To the "
        + "northwest, the Citadel wall rises behind the buildings.\n");
    add_item(({"citadel wall", "citadel"}), "To the northwest, the great "
        + "wall of the Citadel "
        + "can be seen rising above the Sixth Circle. The tall White Tower "
        + "rises from within.\n");


    /* This item is unique to gate rooms, but differs for each */

    add_item(({"gates", "sixth gate", "gate"}), "The two doors look "
        + "well-made and very strong. Although they can be pushed open "
        + "with almost no effort from this side, they are closely guarded "
        + "on the other. Only those with the password are permitted to "
        + "pass to this side.\n");


    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    add_sixth_circle_tells();

    /* These tells are unique to this room */

    add_tell("The sounds of horses can be heard to the northeast.\n");
    add_tell("A citizen in the robes of a healer passes quickly down "
        + "the street.\n");

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

