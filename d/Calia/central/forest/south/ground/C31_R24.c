//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C31_R24", ({"C31_R23", "C32_R23",
        "C32_R24", "C32_R25", "C31_R25", "C30_R25", "C30_R24", "C30_R23"}),
        ({"oak", "birch", "hickory"}));
    }
