#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple " +
        "which leads off to the northwest. A stairway can be seen to the " +
        "southeast and to the west is a small storeroom. Both the floor and " +
        "walls are bare.\n");

    add_exit( DUNGONE + "store2.c", "west" );
    add_exit( DUNGONE + "corr9.c", "northwest" );
    add_exit( BLACK   + "stair0.c", "southeast" );
}
