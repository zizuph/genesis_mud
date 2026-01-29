//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C42_R29", ({"C42_R28", "C43_R28", "C43_R29",
        0, 0, 0, "C41_R29", "C41_R28"}),
        ({"oak", "birch", "cedar"}), ({"thicket"}), 0, "northwest");
    }
