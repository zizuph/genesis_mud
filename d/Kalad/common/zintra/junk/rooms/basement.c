inherit "/std/room.c";
#include <stdproperties.h>
#include "../defs.h"

void
create_room()
{
    set_short("Basement");
    set_long( BS(
"This is a damp, dark underground room beneath other underground rooms.  " +
"The walls here are smooth, but lose their definition to the north.  To the " +
"west you hear some strange noises.  There is a rickety staircase here, " +
"leading up.\n"));

    add_exit(G_ROOMS + "dungeon", "west", 0);
    add_exit(G_ROOMS + "cavern", "north", 0);
    add_exit(G_ROOMS + "ghall1", "up", 0);

    add_item(({"lanterns", "lantern"}), break_string(
"They are rusty, smoky, and in great need of more oil.  Unfortuantely for " +
"you, they are firmly attached to the wall.\n", 78));

    INSIDE
}








