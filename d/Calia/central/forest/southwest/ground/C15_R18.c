//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C15_R18", ({"C15_R17", "C16_R17", "C16_R18",
        "C16_R19", 0, 0, 0, "C14_R17"}),
        ({"sycamore", "oak", "elm", "birch"}), ({"thicket"}));
    }
