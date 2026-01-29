//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C42_R25", ({"C42_R24", "C43_R24",
        "C43_R25", "C43_R26", "C42_R26", "C41_R26", "C41_R25", "C41_R24"}),
        ({"oak", "birch", "hickory"}));
    }
