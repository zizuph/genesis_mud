inherit "/std/room.c";
#include <stdproperties.h>
#include "../defs.h"

void
create_room()
{
    set_short("Cavern");
    set_long(break_string(
"A beautiful, natural cavern, this room looks out of place.  Your light " +
"is reflected off of millions of crystals embedded in the walls.  You " +
"briefly wonder why the construction was never completed in this area, but " +
"the sight is certaily worth it.  To the south is the basement, and there " +
"are various other small tunnels leading off into other directions.\n", 78));

    add_exit(G_ROOMS + "sewers", "north", "@@block");
    add_exit(G_ROOMS + "basement", "south", 0);
    add_exit(G_ROOMS + "???", "east", "@@block");
    add_exit(G_ROOMS + "mountains", "northeast", "@@block");
    add_exit(G_ROOMS + "???", "northwest", "@@block");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
}

int
block()
{
    write("You would easily get lost in the caverns, at this point.\n");
    return 1;
}






