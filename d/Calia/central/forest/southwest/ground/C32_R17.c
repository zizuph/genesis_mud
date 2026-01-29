//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C32_R17", ({"C32_R16", 0, 0, 0, "C32_R18",
        "C31_R18", "C31_R17", "C31_R16"}),
        ({"sycamore", "oak"}), ({"thicket"}));
    }
