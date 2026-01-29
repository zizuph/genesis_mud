//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C19_R21", ({"C19_R20", "C20_R20", "C20_R21",
        "C20_R22", "C19_R22", 0, "C18_R21", "C18_R20"}),
        ({"sycamore", "oak", "elm", "birch"}), ({"thicket"}));
    }
