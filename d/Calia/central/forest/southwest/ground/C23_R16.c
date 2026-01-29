//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C23_R16", ({0, 0, "C24_R16", "C24_R17",
        "C23_R17", "C22_R17", "C22_R16", 0}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
