/* Basic door with lock, coded by Shiva. Used by Marisol
 * (02/23/99) in the Castle at Ovejuno in Emerald. */

#include "../../defs.h"

inherit CASTLE_DOOR2;

void
create_castle_door()
{
    set_long("A dark brown door with a brass door-knob.\n");
    set_adj(({ "dark-brown", "dark", "brown" }));
    set_short("dark-brown door");

    query_locks()->lock();
}
