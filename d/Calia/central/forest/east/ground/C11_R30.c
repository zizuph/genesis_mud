//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C11_R30", ({"C11_R29", "C12_R29",
        "C12_R30", "C12_R31", "C11_R31", "C10_R31", "C10_R30", "C10_R29"}),
        ({"spruce", "balsam", "fir"}));
    }
