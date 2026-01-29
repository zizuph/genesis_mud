//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C11_R24", ({"C11_R23", "C12_R23", "C12_R24",
        "C12_R25", 0, 0, "C10_R24", "C10_R23"}),
        ({"sycamore", "oak"}), ({"thicket"}));
    }
