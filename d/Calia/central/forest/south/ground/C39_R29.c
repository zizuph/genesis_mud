//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C39_R29", ({"C39_R28", "C40_R28", "C40_R29",
        0, 0, 0, "C38_R29", "C38_R28"}),
        ({"oak", "birch", "cedar"}), ({"thicket"}), 0, "northwest");
    }
