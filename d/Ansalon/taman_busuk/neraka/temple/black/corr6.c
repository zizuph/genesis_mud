#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple " +
        "which leads off northeast and southwest. To the west is " +
        "a small storeroom.\n");

    add_exit( BLUE + "store.c", "west" );
    add_exit( BLUE + "corr7.c", "northeast" );
    add_exit( BLUE + "corr5.c", "southwest" );
}
