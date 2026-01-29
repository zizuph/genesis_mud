#pragma strict_types

#include "defs.h"

inherit TEMPLE + "std_hall.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("In the Great Hall of Audience");
    set_long("You are standing just north of a high platform in the middle " +
        "of the Great Hall of Audience. The chamber spreads out in all " +
        "other directions and the domed ceiling rises high above you and " +
        "a slender bridge reaches to the platform\n");

    add_item(({"bridge", "slender bridge"}),
        "A slender bridge of rock runs from an entrance higher up on the " +
        "northern wall all across the hall to a slightly higher platform " +
        "in the centre of the hall. It is made of black rock and seems to " +
        "defy the laws of gravity making it seem as if it will break at any " +
        "moment.\n");

    add_item(({"centre", "middle", "platform", "high platform"}), 
        "There seems to be a higher platform standing in the very middle of " +
        "this large hall. It is hard to get a good look at it from here.\n");

    add_exit( TEMPLE + "hall1.c", "north" );
    add_exit( TEMPLE + "altar.c", "south" );
    add_exit( TEMPLE + "hall4.c", "east" );
    add_exit( TEMPLE + "hall2.c", "west" );
    add_exit( TEMPLE + "hall6.c", "southeast" );
    add_exit( TEMPLE + "hall5.c", "southwest" );
}
