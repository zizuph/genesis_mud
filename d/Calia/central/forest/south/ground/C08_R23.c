//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C08_R23", ({"C08_R22", "C09_R22", "C09_R23",
        0, 0, 0, "C07_R23", "C07_R22"}),
        ({"sycamore", "oak"}), ({"thicket"}));
    }
