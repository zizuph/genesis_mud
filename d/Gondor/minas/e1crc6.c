/*
 *  /d/Gondor/minas/e1crc6.c
 *
 *  Main Street, Sixth Circle
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
    set_streetname("Main Street");
    set_areaname("eastern");
    set_streettype("broad street");
    set_activity(0);
    set_wealth(2);

    add_exit(INNER_MINAS + "/e2crc6", "north", 0);
    add_exit(INNER_MINAS + "/gate6", "southwest", 0);

    /* This extraline is unique to each street room */

    set_extraline("To the southwest you see the Sixth Gate, which will "
        + "take you out to the Fifth Circle of Minas Tirith. North, the "
        + "Main Street comes to the entrance of the tunnel leading through "
        + "the Citadel wall and to the White Tower of Ecthelion.");

    /* These items are similar in all streets on all levels */

    add_street_items();

    /* These items are unique to the specific streets on this circle */

    add_sixth_circle_items();

    /* These items are unique to this room */

    add_item(({"citadel wall", "citadel"}), "To the west, the great "
        + "wall of the Citadel "
        + "can be seen rising above the Sixth Circle. The tall White Tower "
        + "rises from within.\n");
    add_item(({"tunnel"}), "A long lamp-lit slope running up to the "
        + "Seventh Gate. It lies to the north of here.\n");
    add_item(({"gates", "sixth gate", "gate"}), "They appear well-made "
        + "and very strong. They lie to the southwest of here.\n");
    add_item(({"wall", "walls"}), "Which one? To the east is the sixth wall. "
        + "To the "
        + "west, the Citadel wall rises behind the buildings.\n");



    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    add_sixth_circle_tells();

    /* These tells are unique to this room */

    add_tell("The sounds of horses can be heard to the north.\n");
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
