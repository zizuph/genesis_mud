/* A test water room. */

#include "testroom.h"
inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Deep blue sea");
    set_long("At the bottom of the deep blue sea.\n");

    add_swim_exit(TR+"wr1", "up", 0, 1);
    add_wade_exit(TR+"wr3", "east", 0, 1);
}

