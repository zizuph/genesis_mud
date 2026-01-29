#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple " +
        "which continues to the northeast and leads off to a stairway " +
        "to the south.\n");

    add_exit( BLUE + "stair0.c", "south" );
    add_exit( BLUE + "corr6.c", "northeast" );
}
