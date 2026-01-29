//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C10_R23", ({"C10_R22", "C11_R22", "C11_R23",
        "C11_R24", "C10_R24", 0, "C09_R23", "C09_R22"}),
        ({"sycamore", "oak"}), ({"thicket"}));
    }
