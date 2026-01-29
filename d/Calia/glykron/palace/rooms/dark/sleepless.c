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
    set_short("The sleepless room");
    set_long(break_string(
        "This is a small trapezoidal-shaped room whose north and west walls " +
        "slope away from you to the northeast.  You see an unmade bed in the " +
	"corner.  " +
        "\n", 70));
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(ROOM("dark_silent"), "south", 0);
    add_exit(ROOM("dark_bronze"), "southwest", 0);
    add_item("bed", "It looks like someone had a sleepless night.\n");
    call_out("reset_room", 1);
}