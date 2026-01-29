//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C25_R23", ({"C25_R22", "C26_R22", "C26_R23",
        "C26_R24", 0, 0, "C24_R23", "C24_R22"}),
        ({"sycamore", "oak", "elm", "birch"}), ({"thicket"}));
    }
