
/* Castle_base_room
 * To be used as a base for the castle first floor in Ovejuno, Emerald.
 * Contain general information
 * Coded by Marisol (09/03/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types;

inherit "/d/Emerald/std/room";

#include "../defs.h"
#include <stdproperties.h>

void
create_castle_room()
{
}

nomask void
create_emerald_room()
{
    set_short("The Lord's residence second floor.");

    add_item(({"residence", "castle"}),
        "The second floor of this residence is mostly dedicated for "+
        "sleeping quarters. The rooms here are clean and simple "+
        "even the Lord and guest's rooms. But compare with the "+
        "unkept outside, the inside of this residence is "+
        "extremely beautiful.\n");

    add_item(({"torches", "torch-lights"}),
        "The torches are set in iron holders. Maybe they are magical "+
        "elven torch-lights. They are too tall to taken away from "+
        "their place.\n");

    add_item("walls",
        "The corridor walls are all covered with a white and blue "+
        "stripes wallpaper.\n");

    add_prop(ROOM_I_INSIDE, 1);

    create_castle_room();
}                                                                  
