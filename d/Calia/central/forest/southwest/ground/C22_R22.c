//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C22_R22", ({"C22_R21", "C23_R21", "C23_R22",
        "C23_R23", 0, 0, "C21_R22", "C21_R21"}),
        ({"sycamore", "oak", "elm", "birch"}), ({"thicket"}));
    }
