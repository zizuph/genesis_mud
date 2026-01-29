/* Basic door with lock, coded by Shiva. Used by Marisol
 * (02/23/99) in the Castle at Ovejuno in Emerald. */

#include "../../defs.h"

inherit CASTLE_DOOR2;

void
create_castle_door()
{
    set_long("An imposing oak door with intricate carvings.\n");
    set_adj(({ "imposing", "oak" }));
}
