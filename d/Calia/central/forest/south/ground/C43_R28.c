//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C43_R28", ({"C43_R27", "C44_R27", "C44_R28",
        0, "C43_R29", "C42_R29", "C42_R28", "C42_R27"}),
        ({"oak", "birch", "cedar"}), ({"thicket"}), 0, "northwest");
    }
