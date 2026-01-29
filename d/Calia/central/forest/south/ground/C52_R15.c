//Room type {R}

inherit "/d/Calia/central/forest/baserooms/base_entrance";

#include "defs.h"

void create_room()
    {
    /*  add_exit(RUST_VILLAGE + ?, "north", 0, 12);  */
    create_forest_entrance("C52_R15", ({0, 0, "C53_R15", "C53_R16",
        "C52_R16", "C51_R16", "C51_R15", 0}),
        ({"oak", "cedar", "elm"}), 0, "thicket", "north", "hill");
    }
