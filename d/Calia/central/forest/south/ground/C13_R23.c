//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C13_R23", ({"C13_R22", "C14_R22",
        "C14_R23", "C14_R24", "C13_R24", "C12_R24", "C12_R23", "C12_R22"}),
        ({"oak", "birch", "hickory"}));
    }
