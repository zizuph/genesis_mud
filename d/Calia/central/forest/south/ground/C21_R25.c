//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C21_R25", ({"C21_R24", "C22_R24",
        "C22_R25", "C22_R26", "C21_R26", "C20_R26", "C20_R25", "C20_R24"}),
        ({"oak", "birch", "hickory"}));
    }
