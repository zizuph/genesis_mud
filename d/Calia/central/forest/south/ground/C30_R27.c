//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C30_R27", ({"C30_R26", "C31_R26", "C31_R27",
        0, 0, 0, "C29_R27", "C29_R26"}),
        ({"oak", "birch", "cedar"}), ({"thicket"}), 0, "northwest");
    }
