//Room type {w}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C42_R28", ({"C42_R27", "C43_R27",
        "C43_R28", "C43_R29", "C42_R29", "C41_R29", "C41_R28", "C41_R27"}),
        ({"oak", "elm", "birch"}), 0, "northwest");
    }
