//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C15_R25", ({"C15_R24", "C16_R24",
        "C16_R25", "C16_R26", "C15_R26", "C14_R26", "C14_R25", "C14_R24"}),
        ({"oak", "birch", "hickory"}), ({"west", "east"}));
    }
