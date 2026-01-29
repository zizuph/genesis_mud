//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C13_R29", ({"C13_R28", "C14_R28",
        "C14_R29", "C14_R30", "C13_R30", "C12_R30", "C12_R29", "C12_R28"}),
        ({"spruce", "balsam", "fir"}));
    }
