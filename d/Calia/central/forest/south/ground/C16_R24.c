//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C16_R24", ({"C16_R23", "C17_R23",
        "C17_R24", "C17_R25", "C16_R25", "C15_R25", "C15_R24", "C15_R23"}),
        ({"oak", "birch", "hickory"}));
    }
