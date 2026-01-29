//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C21_R23", ({"C21_R22", "C22_R22",
        "C22_R23", "C22_R24", "C21_R24", "C20_R24", "C20_R23", "C20_R22"}),
        ({"oak", "birch", "hickory"}));
    }
