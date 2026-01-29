//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C23_R25", ({"C23_R24", "C24_R24",
        "C24_R25", "C24_R26", "C23_R26", "C22_R26", "C22_R25", "C22_R24"}),
        ({"oak", "birch", "hickory"}));
    }
