//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C44_R26", ({"C44_R25", 0, 0, 0, "C44_R27",
        "C43_R27", "C43_R26", "C43_R25"}),
        ({"oak", "birch", "cedar"}), ({"thicket"}), 0, "northwest");
    }
