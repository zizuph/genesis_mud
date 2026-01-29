//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C38_R26", ({"C38_R25", "C39_R25",
        "C39_R26", "C39_R27", "C38_R27", "C37_R27", "C37_R26", "C37_R25"}),
        ({"oak", "birch", "hickory"}), ({"west", "east"}));
    }
