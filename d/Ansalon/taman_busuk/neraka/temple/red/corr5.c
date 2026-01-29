#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple " +
        "which leads off northwest and east.\n");

    add_exit( RED + "corr4.c", "northwest" );
    add_exit( RED + "corr6.c", "east" );
}
