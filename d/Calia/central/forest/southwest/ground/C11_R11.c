//Room type {1}

inherit "/d/Calia/central/forest/baserooms/base_entrance";

#include "defs.h"

void create_room()
    {
    add_exit("/d/Calia/uhclem/workroom", "northwest", 0, 2);
    create_forest_entrance("C11_R11", ({0, 0, "C12_R11", "C12_R12", 0,
        0, 0, 0}),
        ({"sycamore", "cedar", "fir"}), ({"northwest", "southeast"}),
        "thicket", "northwest");
    }
