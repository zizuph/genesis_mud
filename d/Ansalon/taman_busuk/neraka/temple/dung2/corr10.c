#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark winding corridor");
    set_long("This is a dark winding corridor deep below the temple. " +
        "It twists and turns while continuing to the east and west. " +
        "Both the floor and walls are bare.\n");

    add_exit( DUNGTWO  + "corr11.c", "east", "@@corridor_wind", 0, 0 );
    add_exit( DUNGTWO  + "corr9.c", "west", "@@corridor_wind", 0, 0 );
}

mixed
corridor_wind()
{
    write("The corridor is long and it twists and turns as you walk " +
        "along it.\n\n");
    return 0;
}



