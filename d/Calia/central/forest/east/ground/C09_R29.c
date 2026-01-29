//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C09_R29", ({"C09_R28", "C10_R28",
        "C10_R29", "C10_R30", "C09_R30", "C08_R30", "C08_R29", "C08_R28"}),
        ({"spruce", "balsam", "fir"}));
    }
