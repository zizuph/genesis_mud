//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C16_R13", ({0, 0, 0, "C17_R14", "C16_R14",
        "C15_R14", "C15_R13", "C15_R12"}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
