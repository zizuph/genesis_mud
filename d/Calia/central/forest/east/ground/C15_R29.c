//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C15_R29", ({"C15_R28", "C16_R28",
        "C16_R29", "C16_R30", "C15_R30", "C14_R30", "C14_R29", "C14_R28"}),
        ({"spruce", "balsam", "fir"}));
    }
