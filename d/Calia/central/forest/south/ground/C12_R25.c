//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C12_R25", ({"C12_R24", "C13_R24", "C13_R25",
        "C13_R26", 0, 0, 0, "C11_R24"}),
        ({"sycamore", "oak"}), ({"thicket"}));
    }
