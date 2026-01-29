#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
reset_room()
{
}

void
create_room()
{
    set_short("The room of evilness");
    set_long(break_string(
        "This is a small trapezoidal-shaped room whose south and east walls " +
        "slope away from you to the northwest.  " +
        "A single torch adorns the wall.  " +
        "All other furnishings in this room seem to have been damaged or " +
	"destroyed.  " +
        "\n", 70));
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(ROOM("dark_lazy"), "south", 0);
    add_exit(ROOM("dark_silver"), "southeast", 0);
    call_out("reset_room", 1);
}