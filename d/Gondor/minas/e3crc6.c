/*
 *  /d/Gondor/minas/e3crc6.c
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

object sign;

public void
create_street()
{
    set_circle("Sixth");
    set_streetname("Stable Street");
    set_areaname("eastern");
    set_streettype("broad street");
    set_activity(0);
    set_wealth(2);


    add_exit(INNER_MINAS + "/tcrc6", "south", 0, 0);
    add_exit(INNER_MINAS + "/n1crc6", "northwest", 0, 0);

    /* This extraline is unique to each street room */

    set_extraline("The street continues northwest along the wall of "
        + "the Citadel among the houses of the Sixth Circle. "
        + "To the south the street runs through a tunnel "
        + "into a towering bastion of stone. To the east there is a large "
        + "garden in front of several large white buildings.");

    /* These items are similar in all streets on all levels */

    add_street_items();

    /* These items are unique to the specific streets on this circle */

    add_sixth_circle_items();

    /* These items are unique to this room */

    add_item(({"citadel wall", "citadel"}), "To the west, the great "
        + "wall of the Citadel "
        + "can be seen rising above the Sixth Circle. The tall White Tower "
        + "rises from within.\n");
    add_item(({"bastion"}), "A towering bastion of stone, formed in part "
        + "from the primeval shaping of the mountain, but also by the "
        + "labour of old. It stands from behind the Seventh Gate, its "
        + "edge sharp as a ship-keel. The bastion rises up from the lowest "
        + "circle even to the topmost. It is crowned by a battlement.\n");
    add_item(({"battlement"}), "The battlement is perched atop the huge "
        + "bastion of rock, facing east.  From here it looks as though "
        + "someone standing upon it would be able to look down from it "
        + "sheer down upon the First Gate seven hundred feet below.\n");
    add_item(({"tunnel"}), "A tunnel through the huge bastion. "
        + "It lies to the south of here.\n");
    add_item(({"wall", "walls"}), "Which one? To the east is the sixth wall. "
        + "To the "
        + "west, the Citadel wall rises behind the buildings.\n");
    add_item(({"building", "buildings"}), "To the east of the street "
        + "are the Houses of Healing. The men and women who labour "
        + "there are deeply skilled in the lore of healing the sick "
        + "and injured. It is said that only the hands of the King "
        + "can surpass the skills of the Healers of Minas Tirith.\n");
    add_item(({"garden"}), "Although many of the gardens in the city "
        + "have fallen into disrepair, the garden of the Healers is "
        + "well-tended and fragrant. You feel the weariness of your "
        + "long travels melt away as you breathe in the scent of "
        + "healing herbs.\n");

    sign = clone_object(INNER_MINAS + "/obj/healer_sign.c");
    sign->move(TO);

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    add_sixth_circle_tells();

    /* These tells are unique to this room */

    add_tell("The sounds of horses can be heard to the northwest.\n");
    add_tell("A citizen in the robes of a healer passes quickly down "
        + "the street.\n");
    add_tell("The scent of healing herbs wafts from the garden.\n");
    add_tell("A soft voice can be heard singing gently to the east.\n");


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

