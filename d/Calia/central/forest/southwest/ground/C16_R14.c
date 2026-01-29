//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C16_R14", ({"C16_R13", 0, "C17_R14",
        "C17_R15", "C16_R15", "C15_R15", "C15_R14", "C15_R13"}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
