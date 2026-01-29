#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Second floor of guard tower");
    set_long("You are on the second floor of "+
        "the guard tower. The walls are made of black stone "+
        "carefully fitted together without mortar. "+
        "Granite flagstones pave the floor. Entries lead to four corner "+
        "rooms, and a granite stairway leads up to the "+
        "next floor.\n");
    add_item((({"floor", "ceiling", "walls", "stone",
        "flagstones", "granite flagstones", "black stone"})),
        "The walls, floor and ceiling are all constructed from the "+
        "same dark stone as the city walls. The large blocks are fitted "+
        "together without mortar.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("tower_ne2", "northeast");
    add_exit("tower_nw2", "northwest");
    add_exit("tower_se2", "southeast");
    add_exit("tower_sw2", "southwest");
    add_exit("tower_3", "up");
    add_exit("guard_tower1", "down");
}
