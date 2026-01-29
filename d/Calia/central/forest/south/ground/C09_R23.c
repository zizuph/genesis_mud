//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C09_R23", ({"C09_R22", "C10_R22", "C10_R23",
        "C10_R24", 0, 0, "C08_R23", "C08_R22"}),
        ({"sycamore", "oak"}), ({"thicket"}));
    }
