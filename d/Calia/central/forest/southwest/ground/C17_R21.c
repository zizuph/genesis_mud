//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C17_R21", ({"C17_R20", "C18_R20", "C18_R21",
        0, 0, 0, "C16_R21", "C16_R20"}),
        ({"sycamore", "oak", "elm", "birch"}), ({"thicket"}));
    }
