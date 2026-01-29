//Room type {J}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C18_R32", ({"C18_R31", 0, 0, 0, 0, 0,
        "C17_R32", "C17_R31"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"west", "northeast"}));
    }
