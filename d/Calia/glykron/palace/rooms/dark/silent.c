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
    set_short("The silent room");
    set_long(break_string(
        "This is a large trapezoidal-shaped room whose north and south walls " +
        "slope away from you to the east.  " +
        "The room seems very quiet and eerie.  " +
        "There is a bed up against the east wall.  " +
        "\n", 70));
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(ROOM("dark_darkroom"), "west", 0);
    add_exit(ROOM("dark_sleepless"), "north", 0);
    add_exit(ROOM("dark_shop"), "south", 0);
    add_item("bed", "Its blue sheets are very old and worn.\n");
    call_out("reset_room", 1);
}