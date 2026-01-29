#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple " +
        "which continues to the south and leads off to a stairway to " +
        "the northwest.\n");

    add_exit( GREEN + "stair0.c", "northwest" );
    add_exit( GREEN + "corr5.c", "south" );
}
