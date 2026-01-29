inherit "/std/room.c";
#include <stdproperties.h>
#include "../defs.h"

void
create_room()
{
    set_short("Guild Hall");
    set_long(break_string(
"You have come to the northern end of a very large hall somewhere under" +
"neath the city of Kalad.  Light is eminating from decrepit lanterns " +
"attached to the walls.  There are many exits here, leading off to some " +
"adjoining rooms.  To the west is a tiny store, and you hear strange noises " +
"eminating from the east.  The hall extends further to the south.\n", 78));

    add_exit(G_ROOMS + "ghall2", "south", 0);
    add_exit(G_ROOMS + "start", "east", 0);
    add_exit(G_ROOMS + "shop", "west", 0);

    add_item(({"lanterns", "lantern"}), break_string(
"They are rusty, smoky, and in great need of more oil.  Unfortuantely for " +
"you, they are firmly attached to the wall.\n", 78));

    add_prop(ROOM_I_INSIDE, 1);
}
