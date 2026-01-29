#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple which " +
        "leads off both east and west. Both the floor and " +
        "walls are bare.\n");


    add_exit( DUNGONE  + "corr3.c", "east" );
    add_exit( DUNGONE  + "corr1.c", "west" );
}
