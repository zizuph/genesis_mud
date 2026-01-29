//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C22_R23", ({"C22_R22", "C23_R22",
        "C23_R23", "C23_R24", "C22_R24", "C21_R24", "C21_R23", "C21_R22"}),
        ({"oak", "birch", "hickory"}));
    }
