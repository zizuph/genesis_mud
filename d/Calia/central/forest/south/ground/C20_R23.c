//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C20_R23", ({"C20_R22", "C21_R22",
        "C21_R23", "C21_R24", "C20_R24", "C19_R24", "C19_R23", "C19_R22"}),
        ({"oak", "birch", "hickory"}));
    }
