#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple " +
        "which leads off north and south. To the east lies a small " +
        "storeroom.\n");

    add_exit( GREEN + "corr4.c", "north" );
    add_exit( GREEN + "corr6.c", "south" );
    add_exit( GREEN + "store.c", "east" );
}
