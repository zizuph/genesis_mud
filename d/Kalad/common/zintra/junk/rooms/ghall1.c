inherit "/std/room.c";
#include <stdproperties.h>
#include "../defs.h"

void
create_room()
{
    set_short("Guild Hall");
    set_long(break_string(
"You have come to the south end of a very large hall somewhere underneath " +
"the city of Kalad.  Light is eminating from decrepit lanterns attached to " +
"the walls.  There are many exits here, leading off to some smaller " +
"adjoining rooms.  There is a dark shop to the east, and a very nasty smell " +
"to the west.  There is a staircase leading down, and an open archway to the " +
"south.  The hall continues to the north.\n", 78));

    add_exit(G_ROOMS + "ghall2", "north", 0);
    add_exit(G_ROOMS + "guard_room", "south", 0);
    add_exit(G_ROOMS + "poison", "east", 0);
    add_exit(G_ROOMS + "bounty", "west", 0);
    add_exit(G_ROOMS + "basement", "down", 0);

    add_item(({"lanterns", "lantern"}), break_string(
"They are rusty, smoky, and in great need of more oil.  Unfortuantely for " +
"you, they are firmly attached to the wall.\n", 78));

    add_prop(ROOM_I_INSIDE, 1);
}
