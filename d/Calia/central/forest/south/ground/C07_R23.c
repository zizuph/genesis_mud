//Room type {D}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C07_R23", ({"C07_R22", "C08_R22", "C08_R23",
        0, 0, 0, 0, "C06_R22"}),
        ({"sycamore", "oak"}), ({"thicket"}), ({"northwest"}));
    }
