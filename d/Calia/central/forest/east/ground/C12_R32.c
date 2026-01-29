//Room type {H}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C12_R32", ({"C12_R31", "C13_R31",
        "C13_R32", 0, 0, 0, 0, "C11_R31"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southwest", "west",
        "northeast"}));
    }
