//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C28_R26", ({"C28_R25", "C29_R25",
        "C29_R26", "C29_R27", "C28_R27", "C27_R27", "C27_R26", "C27_R25"}),
        ({"oak", "birch", "hickory"}), ({"west", "east"}));
    }
