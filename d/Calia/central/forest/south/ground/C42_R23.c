//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C42_R23", ({"C42_R22", "C43_R22",
        "C43_R23", "C43_R24", "C42_R24", "C41_R24", "C41_R23", "C41_R22"}),
        ({"oak", "birch", "hickory"}));
    }
