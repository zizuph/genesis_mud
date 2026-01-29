//Room type {@}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C43_R27", ({"C43_R26", "C44_R26",
        "C44_R27", "C44_R28", "C43_R28", "C42_R28", "C42_R27", "C42_R26"}),
        ({"oak", "birch", "hickory"}), ({"west", "east"}), "northwest");
    }
