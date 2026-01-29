/*
 * kitchen.c
 *
 * This is the kitchen off of The Wild Rover, the village
 * pub. At the time of coding, it has no meaning to players,
 * who can't even enter it, but is more of a 'hiding' spot
 * for the landlord to run to when attacked. This might
 * change, however, but not in the forseeable future unless
 * someone thinks up a reason for it ;)
 *
 * Khail - APril 4 /97
 */
#pragma strict_types

#include "room.h"
#include <stdproperties.h>

inherit "/d/Khalakhor/std/room";

/*
 * Function name: create_khalakhor_room
 * Description  : Turn this object into a kitchen
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_room()
{
    set_short("the kitchen of The Wild Rover");
    set_long("   This is the kitchen of The Wild Rover pub. " +
        "It's built quite similarly to the main room " +
        "itself, with the same stone walls and low ceiling. " +
        "In the center of the room, a large wooden table " +
        "is covered in an assortment of pots, pans, spices, " +
        "and various cooking utensils. A couple of iron stoves " +
        "stand against one wall, and an open fireplace " +
        "sports a large spit for open-flame roasting.\n");

    INSIDE;

    add_exit(ROOM + "pub", "west");
}

