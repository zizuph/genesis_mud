//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C32_R16", ({"C32_R15", 0, 0, 0, "C32_R17",
        "C31_R17", "C31_R16", "C31_R15"}),
        ({"sycamore", "oak"}), ({"thicket"}));
    }
