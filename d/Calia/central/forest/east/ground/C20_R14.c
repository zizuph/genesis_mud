//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C20_R14", ({"C20_R13", "C21_R13",
        "C21_R14", "C21_R15", "C20_R15", "C19_R15", "C19_R14", "C19_R13"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"east", "west"}));
    }
