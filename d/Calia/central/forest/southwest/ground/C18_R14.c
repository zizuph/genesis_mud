//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C18_R14", ({0, 0, "C19_R14", "C19_R15",
        "C18_R15", "C17_R15", "C17_R14", 0}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
