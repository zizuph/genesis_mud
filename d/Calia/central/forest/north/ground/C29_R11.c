//Room type 2

inherit "/d/Calia/central/forest/baserooms/base_entrance";

#include "defs.h"

void
create_room()

{

    add_exit(BOG_OUTER + "ground/C32_R32", "north", 0, 2);

    create_forest_entrance("C29_R11", ({0, 0, "C30_R11", "C30_R12",
        "C29_R12", "C28_R12", "C28_R11", 0}),
        ({"balsam", "fir", "beech"}), 0, "bog", "north");

}

