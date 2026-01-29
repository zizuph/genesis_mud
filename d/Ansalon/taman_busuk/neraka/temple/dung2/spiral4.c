#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("The top of a spiraling stairway");
    set_long("You are standing somewhere on a narrow spiraling stairway. It is " +
        "roughly carved out of the stone and somewhat uneaven and it continues " +
        "both up and down.\n");

    add_exit( DUNGTWO + "spiral3.c", "up", "@@spiral_up", 10 + random(5), 0 );
    add_exit( DUNGTHREE + "spiral5.c", "down", "@@spiral_down", 10 + random(5), 0 );
}

mixed
spiral_up()
{
    write("You walk up the spiraling stairway.\n\n");
    return 0;
}

mixed
spiral_down()
{
    write("You walk down the spiraling stairway.\n\n");
    return 0;
}

