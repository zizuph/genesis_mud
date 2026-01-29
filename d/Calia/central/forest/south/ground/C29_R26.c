//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C29_R26", ({"C29_R25", "C30_R25",
        "C30_R26", "C30_R27", "C29_R27", "C28_R27", "C28_R26", "C28_R25"}),
        ({"oak", "birch", "hickory"}), ({"west", "east"}));
    }
