//Room type 4

inherit "/d/Calia/central/forest/baserooms/base_entrance";

#include "defs.h"

void
create_room()

{

    add_exit(BOG_OUTER + "ground/C36_R32", "northwest", 0, 2);

    create_forest_entrance("C34_R11", ({0, 0, 0, "C35_R12", "C34_R12",
        "C33_R12", "C33_R11", 0}),
        ({"balsam", "fir", "beech"}), 0, "bog", "northwest");

}

