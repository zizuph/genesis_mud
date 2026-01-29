//Room type {@}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C42_R27", ({"C42_R26", "C43_R26",
        "C43_R27", "C43_R28", "C42_R28", "C41_R28", "C41_R27", "C41_R26"}),
        ({"oak", "birch", "hickory"}), ({"west", "east"}), "northwest");
    }
