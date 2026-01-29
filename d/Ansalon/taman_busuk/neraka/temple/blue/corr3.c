#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A bend in a corridor");
    set_long("You are standing at a bend in a corridor in the " +
        "temple. It opens up into a larger chamber to the west and " +
        "continues towards the southeast. The black walls are lined " +
        "with torches which shed some light along the corridor.\n");

    add_item(({"corridor", "section", "path"}),
        "This part of the corridor is wide and seemingly straight, leading " +
        "towards the centre of the temple.\n");

    add_exit( BLUE + "achamber.c", "west" );
    add_exit( BLUE + "corr2.c", "southeast" );
}
