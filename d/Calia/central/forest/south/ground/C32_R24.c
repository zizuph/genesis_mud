//Room type {Q}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C32_R24", ({"C32_R23", "C33_R23",
        "C33_R24", "C33_R25", "C32_R25", "C31_R25", "C31_R24", "C31_R23"}),
        ({"oak", "birch", "hickory"}), ({"southwest", "east"}));
    }
