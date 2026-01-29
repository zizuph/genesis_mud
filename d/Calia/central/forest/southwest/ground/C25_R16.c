//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C25_R16", ({0, "C26_R15", "C26_R16",
        "C26_R17", "C25_R17", "C24_R17", "C24_R16", 0}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
