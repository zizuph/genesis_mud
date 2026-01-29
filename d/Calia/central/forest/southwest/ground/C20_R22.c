//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C20_R22", ({"C20_R21", "C21_R21", "C21_R22",
        0, 0, 0, "C19_R22", "C19_R21"}),
        ({"sycamore", "oak", "elm", "birch"}), ({"thicket"}));
    }
