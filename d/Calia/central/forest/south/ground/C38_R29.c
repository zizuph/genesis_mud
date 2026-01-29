//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C38_R29", ({"C38_R28", "C39_R28", "C39_R29",
        0, 0, 0, 0, "C37_R28"}),
        ({"oak", "birch", "cedar"}), ({"thicket"}), 0, "northwest");
    }
