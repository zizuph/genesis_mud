#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>

inherit TEMPLE + "std_base";

void
create_temple_room()
{
    set_short("On a stone balcony");
    set_long("This is a huge stone balcony situated on the side of " +
        "a spiraling tower of the temple. It is semi-circular and it " +
        "has no protective railing around it.\n");

    add_item(({"railing", "protective railing"}),
        "You squint hard, trying to see a railing that doesn't exist, " +
        "but to no avail.\n");
    add_item(({"balcony", "huge balcony", "stone balcony"}),
        "As you study the balcony more carfully, you notice that the " +
        "stone has been scraped by large sharp claws.\n");

    remove_prop(ROOM_I_INSIDE);

    add_exit( WHITE + "stair4.c", "southeast" );
}
