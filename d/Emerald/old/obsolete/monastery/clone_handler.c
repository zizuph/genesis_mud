inherit "/d/Emerald/std/clone_handler";

#include "defs.h"

/* Loaded by m1_00, m1_32, m3_02, m3_01 */

void
create_clone_handler()
{
    set_default_area("/d/Emerald/monastery/");

    add_clone(MONASTERY_NPC + "skeleton", CH_SKELETON_ID, 8, 
        MONASTERY_DIR + "m0_*");

    add_clone(MONASTERY_NPC + "undmonk1", 3, 5,
        MONASTERY_DIR + "m1_*");

    add_clone(MONASTERY_NPC + "undmonk2", 4, 7,
        MONASTERY_DIR + "m1_*");

    set_excluded_destinations(({ MONASTERY_DIR + "m1_32",
                                 MONASTERY_DIR + "m3_02",
                                 MONASTERY_DIR + "m3_01",
                                 MONASTERY_DIR + "*_base" }));
}
