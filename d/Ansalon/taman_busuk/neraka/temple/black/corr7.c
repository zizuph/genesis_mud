#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple " +
        "which leads off both southwest and to the east lies a " +
        "stone stairway.\n");

    add_exit( BLACK + "stair0.c", "east" );
    add_exit( BLUE + "corr6.c", "southwest" );
}
