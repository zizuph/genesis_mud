//Room type X

inherit "/d/Calia/central/bog/outer/ground/base_bog";

#include "defs.h"

void
create_room()
    {
    add_exit(FOREST_NORTH + "ground/C29_R11", "south", 0, 10);
    create_bog(({"C32_R31", "C33_R31", 0, 0, 0, 0, 0, "C31_R31"}));
    }
