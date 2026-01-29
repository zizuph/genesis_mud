//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C41_R24", ({"C41_R23", "C42_R23",
        "C42_R24", "C42_R25", "C41_R25", "C40_R25", "C40_R24", "C40_R23"}),
        ({"oak", "birch", "hickory"}));
    }
