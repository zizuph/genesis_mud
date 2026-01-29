inherit "/d/Emerald/std/clone_handler";

#include "/d/Emerald/north_shore/outpost/defs.h"

void
create_clone_handler()
{
    set_default_area(OUTPOST1_DIR);

    add_clone(OUTPOST1_NPC_DIR + "outpost_sargent",5, 1, 
        OUTPOST1_DIR + "outpost10");

    add_clone(OUTPOST1_NPC_DIR + "outpost_lt",6, 1, 
        ({ OUTPOST1_DIR + "outpost??.c", OUTPOST1_DIR + "??tower??.c" }));

    add_clone(OUTPOST1_NPC_DIR + "outpost_guard", 1, 10,
        ({ OUTPOST1_DIR + "outpost??.c", OUTPOST1_DIR + "??tower??.c" }));

    add_clone(OUTPOST1_NPC_DIR + "outpost_cook", 2, 1,
        OUTPOST1_DIR + "outpost07");

    add_clone(OUTPOST1_NPC_DIR + "outpost_elite", 3, 3,
       ({ OUTPOST1_DIR + "outpost??.c"}));

    add_clone(OUTPOST1_NPC_DIR + "outpost_captain", 4, 1,
        OUTPOST1_DIR + "outpost10");
}
