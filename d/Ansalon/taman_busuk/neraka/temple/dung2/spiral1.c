#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("The top of a spiraling stairway");
    set_long("You are at the top of narrow spiraling stairway. It is " +
        "roughly carved out of the stone and somewhat uneaven. To the " +
        "south is a narrow corridor.\n");

    add_exit( DUNGTWO + "corr1.c", "south" );
    add_exit( DUNGTWO + "spiral2.c", "down", "@@spiral_down", 10 + random(5), 0 );
}

mixed
spiral_down()
{
    write("You walk down the spiraling stairway.\n\n");
    return 0;
}
