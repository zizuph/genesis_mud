//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C15_R24", ({"C15_R23", "C16_R23",
        "C16_R24", "C16_R25", "C15_R25", "C14_R25", "C14_R24", "C14_R23"}),
        ({"oak", "birch", "hickory"}));
    }
