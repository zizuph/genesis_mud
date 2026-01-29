//Room type 3

inherit "/d/Calia/central/forest/baserooms/base_entrance";

#include "defs.h"

void
create_room()

{

    add_exit(BOG_OUTER + "ground/C34_R32", "north", 0, 2);

    create_forest_entrance("C31_R11", ({0, 0, "C32_R11", "C32_R12",
        "C31_R12", "C30_R12", "C30_R11", 0}),
        ({"balsam", "fir", "beech"}), 0, "bog", "north");

}

