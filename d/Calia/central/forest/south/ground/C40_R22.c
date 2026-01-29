//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C40_R22", ({"C40_R21", "C41_R21",
        "C41_R22", "C41_R23", "C40_R23", "C39_R23", "C39_R22", "C39_R21"}),
        ({"oak", "birch", "hickory"}), ({"west", "east"}));
    }
