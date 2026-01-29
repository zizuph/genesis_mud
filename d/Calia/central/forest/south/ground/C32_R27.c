//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C32_R27", ({"C32_R26", "C33_R26", "C33_R27",
        0, 0, 0, "C31_R27", "C31_R26"}),
        ({"oak", "birch", "cedar"}), ({"thicket"}), 0, "northwest");
    }
