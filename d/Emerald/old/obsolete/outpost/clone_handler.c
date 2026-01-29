inherit "/d/Emerald/std/clone_handler";

#include "/d/Emerald/outpost1/defs.h"

void
create_clone_handler()
{
    set_default_area("/d/Emerald/outpost1/");

    add_clone(OUTPOST1_NPC_DIR + "outpost_sergeant",5, 1, 
        OUTPOST1_DIR + "outpost10");

    add_clone(OUTPOST1_NPC_DIR + "outpost_lt",6, 1, 
        ({ OUTPOST1_DIR + "outpost??.c", OUTPOST1_DIR + "??tower??.c" }));

    add_clone(OUTPOST1_NPC_DIR + "outpost_guard", 1, 10,
        ({ OUTPOST1_DIR + "outpost??.c", OUTPOST1_DIR + "??tower??.c" }));

    add_clone(OUTPOST1_NPC_DIR + "outpost_cook", 2, 1,
        OUTPOST1_DIR + "outpost04");

    add_clone(OUTPOST1_NPC_DIR + "outpost_elite", 3, 3,
       ({ OUTPOST1_DIR + "outpost??.c"}));

    add_clone(OUTPOST1_NPC_DIR + "outpost_captain", 4, 1,
        OUTPOST1_DIR + "outpost10");
}