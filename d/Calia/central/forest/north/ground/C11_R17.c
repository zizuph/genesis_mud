//Room type W

inherit "/d/Calia/central/forest/baserooms/base_entrance";

#include "defs.h"

void
create_room()

{

    add_exit("/d/Calia/uhclem/workroom", "west", 0, 2);

    create_forest_entrance("C11_R17", ({"C11_R16", "C12_R16",
        "C12_R17", "C12_R18", "C11_R18", 0, 0, 0}),
        ({"cedar", "fir", "beech"}), ({"east", "west"}), "thicket", "west");

}

