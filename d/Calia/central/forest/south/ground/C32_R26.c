//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C32_R26", ({"C32_R25", "C33_R25",
        "C33_R26", "C33_R27", "C32_R27", "C31_R27", "C31_R26", "C31_R25"}),
        ({"oak", "birch", "hickory"}));
    }
