//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C17_R14", ({0, 0, "C18_R14", "C18_R15",
        "C17_R15", "C16_R15", "C16_R14", "C16_R13"}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
