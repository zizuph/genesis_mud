//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C26_R24", ({"C26_R23", "C27_R23", "C27_R24",
        0, 0, 0, 0, "C25_R23"}),
        ({"sycamore", "oak", "elm", "birch"}), ({"thicket"}));
    }
