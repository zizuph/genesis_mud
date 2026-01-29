//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C18_R21", ({"C18_R20", "C19_R20", "C19_R21",
        "C19_R22", 0, 0, "C17_R21", "C17_R20"}),
        ({"sycamore", "oak", "elm", "birch"}), ({"thicket"}));
    }
