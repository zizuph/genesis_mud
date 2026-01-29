#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple " +
        "which continues to the north and leads off to a stairway to " +
        "the south.\n");

    add_exit( GREEN + "corr5.c", "north" );
    add_exit( RED + "stair0.c", "south" );
}
