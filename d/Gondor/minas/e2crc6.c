/*
 *  /d/Gondor/minas/e2crc6.c
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


    add_exit(INNER_MINAS + "/tcrc6", "north", 0, 0);
    add_exit(INNER_MINAS + "/tcrc7", "west", 0, 0);
    add_exit(INNER_MINAS + "/e1crc6", "south", 0, 0);

    /* This extraline is unique to each street room */

    set_extraline("The Main Street continues north through a tunnel "
        + "into a towering bastion of stone. Another tunnel enters "
        + "the rock to the west, leading up a long lamp-lit slope "
        + "to the Seventh Gate. The Main Street also leads south "
        + "toward the Sixth Gate.");

    /* These items are similar in all streets on all levels */

    add_street_items();

    /* These items are unique to the specific streets on this circle */

    add_sixth_circle_items();

    /* These items are unique to this room */

    add_item(({"citadel wall", "citadel"}), "To the west, the great "
        + "wall of the Citadel "
        + "can be seen rising above the Sixth Circle. The tall White Tower "
        + "rises from within.\n");
    add_item(({"tunnel"}), "Which one?  There is a north tunnel and "
        + "a west tunnel.\n");
    add_item(({"west tunnel", "slope"}), "A long lamp-lit slope "
        + "running up to the "
        + "Seventh Gate. It lies to the west of here.\n");
    add_item(({"north tunnel"}), "A tunnel through the huge bastion. "
        + "It lies to the north of here.\n");
    add_item(({"gates", "sixth gate", "gate", "seventh gate"}), "No gates "
        + "can be seen "
        + "from here.  The Seventh Gate lies to the west, while the "
        + "Sixth Gate lies to the south.\n");
    add_item(({"bastion"}), "A towering bastion of stone, formed in part "
        + "from the primeval shaping of the mountain, but also by the "
        + "labour of old. It stands from behind the Seventh Gate, its "
        + "edge sharp as a ship-keel. The bastion rises up from the lowest "
        + "circle even to the topmost. It is crowned by a battlement.\n");
    add_item(({"battlement"}), "The battlement is perched atop the huge "
        + "bastion of rock, facing east.  From here it looks as though "
        + "someone standing upon it would be able to look down from it "
        + "sheer down upon the First Gate seven hundred feet below.\n");
    add_item(({"wall", "walls"}), "Which one? To the east is the sixth wall. "
        + "To the "
        + "west, the Citadel wall rises behind the buildings.\n");
    add_item(({"stone"}), "The bastion is part of Mount Mindolluin itself, "
        + "and as such is made from the stone that forms the mountain.\n");



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

