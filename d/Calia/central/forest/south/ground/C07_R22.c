//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C07_R22", ({"C07_R21", "C08_R21", "C08_R22",
        "C08_R23", "C07_R23", 0, "C06_R22", "C06_R21"}),
        ({"sycamore", "oak"}), ({"thicket"}));
    }
