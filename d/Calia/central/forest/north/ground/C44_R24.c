//Room type F

inherit "/d/Calia/central/forest/baserooms/base_entrance";

#include "defs.h"

void
create_room()

{

    add_exit(FOREST_EAST + "ground_level/C01_R28", "east", 0, 2);

    create_forest_entrance("C44_R24", ({"C44_R23", 0, 0, 0, "C44_R25",
        "C43_R25", "C43_R24", "C43_R23"}),
        ({"cedar", "fir"}), ({"east", "west"}), "thicket", "east");

}

