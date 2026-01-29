//Room type {T}

inherit "/d/Calia/central/forest/baserooms/base_entrance";

#include "defs.h"

void create_room()
    {
    /*  add_exit(TOAD_IN_OAK_ROOMS + ?, "east", 0, 2);  */
    create_forest_entrance("C44_R27", ({"C44_R26", 0, 0, 0, "C44_R28",
        "C43_R28", "C43_R27", "C43_R26"}),
        ({"sycamore", "elm"}), ({"west", "east"}), "thicket", "east", "hill");
    }
