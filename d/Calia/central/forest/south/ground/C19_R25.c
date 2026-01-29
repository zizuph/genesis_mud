//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C19_R25", ({"C19_R24", "C20_R24",
        "C20_R25", "C20_R26", "C19_R26", "C18_R26", "C18_R25", "C18_R24"}),
        ({"oak", "birch", "hickory"}), ({"west", "east"}));
    }
