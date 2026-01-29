//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C32_R19", ({"C32_R18", 0, 0, 0, "C32_R20",
        "C31_R20", "C31_R19", "C31_R18"}),
        ({"sycamore", "oak"}), ({"thicket"}));
    }
