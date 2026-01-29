//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C16_R23", ({"C16_R22", "C17_R22",
        "C17_R23", "C17_R24", "C16_R24", "C15_R24", "C15_R23", "C15_R22"}),
        ({"oak", "birch", "hickory"}));
    }
