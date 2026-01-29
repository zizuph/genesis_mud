//Room type {K}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C18_R29", ({"C18_R28", 0, 0, 0, "C18_R30",
        "C17_R30", "C17_R29", "C17_R28"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southeast", "west"}));
    }
