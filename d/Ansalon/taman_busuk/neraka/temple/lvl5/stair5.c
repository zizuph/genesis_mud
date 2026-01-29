#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    ::create_temple_room();

     set_short("On a winding stairway");
    set_long("You are standing on the top floor landing of a spiraling " +
        "stone stairway in the Temple of Darkness. The stairway continues " +
        "downwards and a narrow archway leads to the northeast from " +
        "which you catch a sniff of fresh air.\n");

    add_exit( LVLFIVE + "balcony.c", "northeast" );
    add_exit( LVLFOUR + "stair4.c", "down" );
}
