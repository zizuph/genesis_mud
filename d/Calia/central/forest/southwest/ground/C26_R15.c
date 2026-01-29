//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C26_R15", ({0, 0, "C27_R15", "C27_R16",
        "C26_R16", "C25_R16", 0, 0}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
