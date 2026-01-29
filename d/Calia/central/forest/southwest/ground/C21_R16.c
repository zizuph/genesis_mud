//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C21_R16", ({0, 0, "C22_R16", "C22_R17",
        "C21_R17", "C20_R17", "C20_R16", "C20_R15"}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
