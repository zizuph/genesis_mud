//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C24_R24", ({"C24_R23", "C25_R23",
        "C25_R24", "C25_R25", "C24_R25", "C23_R25", "C23_R24", "C23_R23"}),
        ({"oak", "birch", "hickory"}));
    }
