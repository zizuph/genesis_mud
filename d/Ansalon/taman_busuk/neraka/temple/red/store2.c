#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_store.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("In a small storeroom");

    set_long("This is a small storeroom deep down in the temple. Boxes " +
        "and crates are piled on each other and in a corner you see some " +
        "barrels.\n");

    add_item("corner", "There are some barrels standing there.\n");

    add_exit( RED + "corr7.c", "southeast" );
}
