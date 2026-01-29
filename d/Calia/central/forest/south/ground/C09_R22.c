//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C09_R22", ({"C09_R21", "C10_R21",
        "C10_R22", "C10_R23", "C09_R23", "C08_R23", "C08_R22", "C08_R21"}),
        ({"oak", "birch", "hickory"}), ({"west", "east"}));
    }
