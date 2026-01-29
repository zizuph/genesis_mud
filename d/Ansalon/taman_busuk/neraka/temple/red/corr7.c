#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple " +
        "which leads off to the west. A stairway can be seen to the " +
        "east and a small storeroom lies to the northwest.\n");

    add_exit( BLUE + "stair0.c", "east" );
    add_exit( RED + "corr6.c", "west" );
    add_exit( RED + "store2.c", "northwest" );
}
