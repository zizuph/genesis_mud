//Room type {K}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C18_R31", ({"C18_R30", 0, 0, 0, "C18_R32",
        "C17_R32", "C17_R31", "C17_R30"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southeast", "west"}));
    }
