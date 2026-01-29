//Room type {=}

inherit "/d/Calia/central/forest/baserooms/base_entrance";

#include "defs.h"

void create_room()
    {
    create_tree("C33_R03", ({0, 0, 0, 0, 0, "C32_R04", "C32_R03", 0}),
        "cedar");
    /*  add_exit("ROOM?", "west", 0, 2);  */
    }
