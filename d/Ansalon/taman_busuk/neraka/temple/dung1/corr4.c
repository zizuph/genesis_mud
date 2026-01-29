#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple. " +
        "It leads off both east and west, but to the northeast is an " +
        "archway leading into a strange cavern. Both the floor and " +
        "walls are bare.\n");

    add_item("archway","It is a smooth stone archway about seven " +
        "feet high.\n");

    add_exit( DUNGONE  + "herbshop.c", "northeast" );
    add_exit( DUNGONE  + "corr5.c", "east" );
    add_exit( DUNGONE  + "corr3.c", "west" );
}
