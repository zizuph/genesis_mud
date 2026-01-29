//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C11_R23", ({"C11_R22", "C12_R22",
        "C12_R23", "C12_R24", "C11_R24", "C10_R24", "C10_R23", "C10_R22"}),
        ({"oak", "birch", "hickory"}));
    }
