//Room type Z

inherit "/d/Calia/central/bog/outer/ground/base_bog";

#include "defs.h"

void
create_room()
    {
    add_exit(FOREST_NORTH + "ground/C26_R34", "southeast", 0, 10);
    create_bog(({"C36_R31", "C37_R31", 0, 0, 0, 0, 0, "C35_R31"}));
    }
