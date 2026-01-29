//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C16_R19", ({"C16_R18", "C17_R18", "C17_R19",
        "C17_R20", "C16_R20", 0, 0, "C15_R18"}),
        ({"sycamore", "oak", "elm", "birch"}), ({"thicket"}));
    }
