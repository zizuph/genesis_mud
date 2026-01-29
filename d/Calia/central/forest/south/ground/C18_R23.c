//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C18_R23", ({"C18_R22", "C19_R22",
        "C19_R23", "C19_R24", "C18_R24", "C17_R24", "C17_R23", "C17_R22"}),
        ({"oak", "birch", "hickory"}));
    }
