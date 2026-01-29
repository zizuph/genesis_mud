#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark winding corridor");
    set_long("This is a dark winding corridor deep below the temple. " +
        "It twists and turns while continuing to the east. To the west " +
        "you see it opens up to a guardroom. Both the floor and walls " +
        "are bare.\n");

    add_exit( DUNGTWO  + "corr8.c", "east", "@@corridor_wind", 0, 0 );
    add_exit( DUNGTWO  + "guard.c", "west" );
}

mixed
corridor_wind()
{
    write("The corridor is long and it twists and turns as you walk " +
        "along it.\n\n");
    return 0;
}



