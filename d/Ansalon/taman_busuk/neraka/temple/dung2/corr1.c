#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor deep below the temple. " +
        "It leads off to the south and a stairway can be seen to the " +
        "north leading down. Both the floor and walls are bare.\n");

    add_exit( DUNGTWO  + "spiral1.c", "north" );
    add_exit( DUNGTWO  + "corr2.c", "south" );
}
