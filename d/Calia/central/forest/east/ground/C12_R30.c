//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C12_R30", ({"C12_R29", "C13_R29",
        "C13_R30", "C13_R31", "C12_R31", "C11_R31", "C11_R30", "C11_R29"}),
        ({"spruce", "balsam", "fir"}));
    }
