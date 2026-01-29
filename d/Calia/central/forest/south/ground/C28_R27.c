//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C28_R27", ({"C28_R26", "C29_R26", "C29_R27",
        0, "C28_R28", "C27_R28", "C27_R27", "C27_R26"}),
        ({"oak", "birch", "cedar"}), ({"thicket"}), 0, "northwest");
    }
