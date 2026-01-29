//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C05_R25", ({"C05_R24", 0, "C06_R25", 0, 0, 0,
        "C04_R25", "C04_R24"}),
        ({"sycamore", "oak"}), ({"thicket"}));
    }
