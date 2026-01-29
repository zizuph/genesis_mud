//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C10_R30", ({"C10_R29", "C11_R29",
        "C11_R30", "C11_R31", "C10_R31", "C09_R31", "C09_R30", "C09_R29"}),
        ({"spruce", "balsam", "fir"}));
    }
