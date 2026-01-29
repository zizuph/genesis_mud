//Room type 1

inherit "/d/Calia/central/forest/baserooms/base_entrance";

#include "defs.h"

void
create_room()

{

    add_exit(BOG_OUTER + "ground/C30_R32", "northeast", 0, 2);

    create_forest_entrance("C26_R11", ({0, 0, "C27_R11", "C27_R12",
        "C26_R12", "C25_R12", 0, 0}),
        ({"balsam", "fir", "beech"}), 0, "bog", "northeast");

}

