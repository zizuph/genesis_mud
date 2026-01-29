//Room type E

inherit "/d/Calia/central/forest/baserooms/base_entrance";

#include "defs.h"

void
create_room()

{

    add_exit(FOREST_EAST + "ground/C19_R14", "east", 0, 2);

    create_forest_entrance("C65_R16", ({"C65_R15", 0, 0, 0, "C65_R17",
        "C64_R17", "C64_R16", "C64_R15"}),
        ({"cedar", "fir"}), ({"east", "west"}), "stream", "east");

}

