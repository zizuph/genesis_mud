//Room type {E}

inherit "/d/Calia/central/forest/baserooms/base_entrance";

#include "defs.h"

void create_room()
    {
    create_forest_entrance("C19_R14", ({"C19_R13", "C20_R13",
        "C20_R14", "C20_R15", "C19_R15", 0, 0, 0}),
        ({"cedar", "fir"}), ({"east", "west"}), "stream", "west");
    add_exit(FOREST_NORTH + "ground/C65_R16", "west", 0, 2);
    }
