//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C33_R25", ({"C33_R24", "C34_R24",
        "C34_R25", "C34_R26", "C33_R26", "C32_R26", "C32_R25", "C32_R24"}),
        ({"oak", "birch", "hickory"}));
    }
