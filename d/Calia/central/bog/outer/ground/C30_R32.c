//Room type W

inherit "/d/Calia/central/bog/outer/ground/base_bog";

#include "defs.h"

void
create_room()
    {
    add_exit(FOREST_NORTH + "ground/C26_R11", "southwest", 0, 10);
    create_bog(({"C30_R31", "C31_R31", 0, 0, 0, 0, 0, "C29_R31"}));
    }
