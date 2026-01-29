inherit "/std/room.c";
#include <stdproperties.h>
#include "../defs.h"

void
create_room()
{
    set_short("Passage");
    set_long(break_string(
"You are in a very dark passage underneath a warehouse in Kalad, running " +
"north and south.  The walls are smooth, and non-descript.\n", 78));

    add_exit(G_ROOMS + "guild_ent1.c", "north", 0);
    add_exit(G_ROOMS + "under_crate", "south", 0);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

}
