//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C33_R27", ({"C33_R26", "C34_R26", "C34_R27",
        "C34_R28", 0, 0, "C32_R27", "C32_R26"}),
        ({"oak", "birch", "cedar"}), ({"thicket"}), 0, "northwest");
    }
