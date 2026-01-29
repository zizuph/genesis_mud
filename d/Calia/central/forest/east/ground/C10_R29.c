//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C10_R29", ({"C10_R28", "C11_R28",
        "C11_R29", "C11_R30", "C10_R30", "C09_R30", "C09_R29", "C09_R28"}),
        ({"spruce", "balsam", "fir"}));
    }
