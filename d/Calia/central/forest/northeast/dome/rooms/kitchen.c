// ROOM:  Dome - kitchen
//        DOME_ROOMS + room07

    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.

        PURPOSE
        Here meals for the dome's occupants are designed 
        and created by culinary geniuses.
        In the food preparation quest, the questor must
        get the cook out of the kitchen to prepare the food.
        This is done by having a different player complement
        the chef in the common lounge.

        AREA HISTORY
        Extensively redesigned over the years, this kitchen
        is now a master chef's delight, producing the most
        exquisite of dishes.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room.c";

#include "defs.h"
#include <stdproperties.h>

// ROOM DEFINITION

void
create_room()
{

    /* DESCRIPTION */

    set_short("Pleasure Dome kitchen");

    set_long("All manner of smells reach your nose as " +
        "you enter this kitchen. The scent of cooking " +
        "meats and breads combine with different " +
        "seasonings to astound your sense of smell. " +
        "Racks on the walls are filled with cooking " +
        "utensils, counters are covered with partially " +
        "prepared meals and ingredients. The kitchen " +
        "stoves fill the room with heat, making it " +
        "uncomfortably warm.\n");

    /* ITEMS */

    add_item(({"smell", "sniff", "scent"}),
        "You smell many different scents, so many its " +
        "hard to isolate indivual scents out of them. " +
        "You can pick out roasting meat, baking bread, " +
        "and several distinctive herb smells.\n");

    /* EXITS */

    add_exit("hall", "north", 0, 05);
    add_exit("storage", "west", 0, 05);
    add_exit("club_entrance", "east", 0, 05);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 50);

    }
