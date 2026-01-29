//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C25_R25", ({"C25_R24", "C26_R24",
        "C26_R25", "C26_R26", "C25_R26", "C24_R26", "C24_R25", "C24_R24"}),
        ({"oak", "birch", "hickory"}), ({"west", "east"}));
    }
