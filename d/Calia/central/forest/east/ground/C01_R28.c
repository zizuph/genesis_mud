//Room type {D}

inherit "/d/Calia/central/forest/baserooms/base_entrance";

#include "defs.h"

void create_room()
    {
    create_forest_entrance("C01_R28", ({0, 0, "C02_R28", 0, 0, 0, 0, 0}),
        ({"spruce", "pine"}), ({"east", "west"}), "thicket", "west");
    add_exit(FOREST_NORTH + "ground_level/C44_R24", "west", 0, 2);
    }
