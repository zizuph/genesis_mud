//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C17_R25", ({"C17_R24", "C18_R24",
        "C18_R25", "C18_R26", "C17_R26", "C16_R26", "C16_R25", "C16_R24"}),
        ({"oak", "birch", "hickory"}), ({"west", "east"}));
    }
