//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C14_R30", ({"C14_R29", "C15_R29",
        "C15_R30", "C15_R31", "C14_R31", "C13_R31", "C13_R30", "C13_R29"}),
        ({"spruce", "balsam", "fir"}));
    }
