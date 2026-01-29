//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C12_R24", ({"C12_R23", "C13_R23", "C13_R24",
        "C13_R25", "C12_R25", 0, "C11_R24", "C11_R23"}),
        ({"sycamore", "oak"}), ({"thicket"}));
    }
