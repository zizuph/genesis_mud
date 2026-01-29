/* Basic door with lock, coded by Shiva. Used by Marisol
 * (02/23/99) in the Castle at Ovejuno in Emerald. */

#include "../../defs.h"

inherit CASTLE_DOOR2;

void
create_castle_door()
{
    set_long("A beige oak door with a simple carving decorating "+
        "the border of the door.\n");
    set_adj(({ "beige", "oak" }));
}
