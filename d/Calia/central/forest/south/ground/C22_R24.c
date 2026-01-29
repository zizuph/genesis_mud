//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C22_R24", ({"C22_R23", "C23_R23",
        "C23_R24", "C23_R25", "C22_R25", "C21_R25", "C21_R24", "C21_R23"}),
        ({"oak", "birch", "hickory"}), ({"west", "east"}));
    }
