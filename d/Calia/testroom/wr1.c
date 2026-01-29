/* A test water room. */

#include "testroom.h"
inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Deep blue sea");
    set_long("Out in the middle of the deep blue sea.\n");

    add_swim_exit(TR+"wr2", "down", 0, 1);
    set_tell_time(60);
    add_tell("The water is cold!\n");
    add_tell("Brrr!\n");
}

