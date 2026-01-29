#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("On a spiraling stairway");
    set_long("You are standing at the bottom of a steep spiraling stairway which has " +
        "been roughly carved out of the stone. It is somewhat uneaven and continues " +
        "up. A short narrow tunnel leads off south to a guardroom.\n");

    add_exit( DUNGTWO + "spiral4.c", "up", "@@spiral_up", 10 + random(5), 0 );
    add_exit( DUNGTHREE + "guard.c", "south" );
}

mixed
spiral_up()
{
    write("You walk up the spiraling stairway.\n\n");
    return 0;
}
