//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C17_R29", ({"C17_R28", "C18_R28",
        "C18_R29", "C18_R30", "C17_R30", "C16_R30", "C16_R29", "C16_R28"}),
        ({"spruce", "balsam", "fir"}));
    }
