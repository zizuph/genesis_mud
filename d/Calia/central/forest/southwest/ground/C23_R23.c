//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C23_R23", ({"C23_R22", "C24_R22", "C24_R23",
        0, 0, 0, 0, "C22_R22"}),
        ({"sycamore", "oak", "elm", "birch"}), ({"thicket"}));
    }
