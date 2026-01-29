//Room type {=}

inherit "/d/Calia/central/forest/baserooms/base_entrance";

#include "defs.h"

void create_room()
    {
    create_forest_entrance("C33_R03", ({"C33_R02", 0, 0, 0, "C33_R04",
        "C32_R04", "C32_R03", "C32_R02"}),
        ({"cedar", "spruce", "pine"}), ({"east", "west"}), "mountain",
            "west");
    /*  add_exit("ROOM?", "west", 0, 2);  */
    }
