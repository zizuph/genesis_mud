inherit "/d/Emerald/std/clone_handler";

#include "defs.h"

void
create_clone_handler()
{
    set_default_area(OVEJUNO_DIR);
 
    add_clone(OVEJUNO_NPC_DIR + "sheep", 2, 3, OVEJUNO_DIR + "pasture*");
    add_clone(OVEJUNO_NPC_DIR + "shepherd01", 3, 1, OVEJUNO_DIR + "pasture*");
    add_clone(OVEJUNO_NPC_DIR + "shepherd02", 3, 1, OVEJUNO_DIR + "pasture*");

    set_excluded_destinations(({ OVEJUNO_DIR + "pastures_base" }));
}

