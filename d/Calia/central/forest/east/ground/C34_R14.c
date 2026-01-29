//Room type {K}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C34_R14", ({0, 0, "C35_R14", "C35_R15",
        "C34_R15", "C33_R15", 0, 0}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southeast", "west"}));
    }
