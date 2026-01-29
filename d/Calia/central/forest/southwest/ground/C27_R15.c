//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C27_R15", ({0, 0, "C28_R15", "C28_R16",
        "C27_R16", "C26_R16", "C26_R15", 0}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
