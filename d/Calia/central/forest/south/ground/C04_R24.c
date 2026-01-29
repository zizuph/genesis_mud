//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C04_R24", ({"C04_R23", 0, "C05_R24",
        "C05_R25", "C04_R25", "C03_R25", "C03_R24", "C03_R23"}),
        ({"sycamore", "oak"}), ({"thicket"}));
    }
