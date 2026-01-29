//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C21_R14", ({"C21_R13", "C22_R13",
        "C22_R14", "C22_R15", "C21_R15", "C20_R15", "C20_R14", "C20_R13"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"east", "west"}));
    }
