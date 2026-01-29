//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C23_R23", ({"C23_R22", "C24_R22",
        "C24_R23", "C24_R24", "C23_R24", "C22_R24", "C22_R23", "C22_R22"}),
        ({"oak", "birch", "hickory"}));
    }
