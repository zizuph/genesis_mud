/* Make a door leading down to the dias.*/

#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("In a narrow corridor");
    set_long("You are standing in a narrow stone corridor. It leads to " +
        "a winding stairway to the east and an archway to the west " +
        "opens up into a small chamber. There is also another " +
        "archway to the northwest leading down some twisted stairs.\n");

    add_item(({"chamber", "small chamber"}), 
        "It is hard to see what the chamber looks like from here. It " +
        "doesn't seem to be large.\n");
    add_item("archway", "It is a smooth stone archway which has been " +
        "carved out of the stone walls.\n");

    add_exit( BLUE + "stair2.c", "east" );
    add_exit( BLUE + "chamber.c", "west" );
    add_exit( BLUE + "landing.c", "northwest","@@stair_notice", 0, 1 );
}

int
stair_notice()
{
    write("You step through the small archway and descend the " +
        "narrow stairs which twist to the south a little.\n\n");
    return 0;
}
