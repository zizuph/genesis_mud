//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C11_R29", ({"C11_R28", "C12_R28",
        "C12_R29", "C12_R30", "C11_R30", "C10_R30", "C10_R29", "C10_R28"}),
        ({"spruce", "balsam", "fir"}));
    }
