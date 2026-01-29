#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple " +
        "which leads off to a stairway to the north and one to the " +
        "southwest. To the south lies a small storeroom.\n");

    add_exit( WHITE + "stair0.c", "north" );
    add_exit( WHITE + "store.c", "south" );
    add_exit( GREEN + "stair0.c", "southwest" );
}
