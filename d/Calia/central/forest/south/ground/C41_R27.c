//Room type {E}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C41_R27", ({"C41_R26", "C42_R26",
        "C42_R27", "C42_R28", "C41_R28", "C40_R28", "C40_R27", "C40_R26"}),
        ({"oak", "birch", "hickory"}), ({"northwest", "east"}), "northwest");
    }
