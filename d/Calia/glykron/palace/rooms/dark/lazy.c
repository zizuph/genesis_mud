#pragma save_binary

inherit "/std/room";
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

void
reset_room()
{
}

void
create_room()
{
    set_short("The clock room");
    set_long(
        "This is a small trapezoidal-shaped room whose north and south walls " +
        "slope away from you to the west.  " +
        "There is a bed up against the west wall, and a huge clock above the " +
	"bed.  " +
        "\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(ROOM("dark_training"), "east", 0);
    add_exit(ROOM("dark_evil"), "north", 0);
    add_item("bed", "The bed has been recently slept in.\n");
    add_item("clock", "The clock no longer runs.\n");
    call_out("reset_room", 1);
}