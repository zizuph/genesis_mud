#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room()
{
    set_short("A hall");
    set_long(break_string(
	 "This is a small trapezoidal-shaped room whose east and west walls "
	+"slope away to the north.  "
	+"\n", 70));
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(ROOM("dark_stairs2"),"south",0);
}