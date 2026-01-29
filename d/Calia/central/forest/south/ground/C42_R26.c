//Room type {w}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C42_R26", ({"C42_R25", "C43_R25",
        "C43_R26", "C43_R27", "C42_R27", "C41_R27", "C41_R26", "C41_R25"}),
        ({"oak", "elm", "birch"}), 0, "northwest");
    }
