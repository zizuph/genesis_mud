//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C19_R23", ({"C19_R22", "C20_R22",
        "C20_R23", "C20_R24", "C19_R24", "C18_R24", "C18_R23", "C18_R22"}),
        ({"oak", "birch", "hickory"}));
    }
