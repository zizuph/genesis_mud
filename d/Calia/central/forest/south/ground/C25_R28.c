//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C25_R28", ({"C25_R27", "C26_R27", "C26_R28",
        0, 0, 0, 0, "C24_R27"}),
        ({"oak", "birch", "cedar"}), ({"thicket"}), 0, "northwest");
    }
