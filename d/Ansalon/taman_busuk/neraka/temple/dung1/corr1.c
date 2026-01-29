#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple " +
        "which leads off to the east. A stairway can be seen to the " +
        "west and to the south is a small storeroom. Both the floor and " +
        "walls are bare.\n");

    add_exit( DUNGONE + "store1.c", "south" );
    add_exit( DUNGONE + "corr2.c", "east" );
    add_exit( WHITE   + "stair0.c", "west" );
}
