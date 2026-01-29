//Room type Y

inherit "/d/Calia/central/bog/outer/ground/base_bog";

#include "defs.h"

void
create_room()
    {
    add_exit(FOREST_NORTH + "ground/C31_R11", "south", 0, 10);
    create_bog(({"C34_R31", "C35_R31", 0, 0, 0, 0, 0, "C33_R31"}));
    }
