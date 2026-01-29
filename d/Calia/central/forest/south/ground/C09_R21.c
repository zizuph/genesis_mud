//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C09_R21", ({0, 0, "C10_R21", "C10_R22",
        "C09_R22", "C08_R22", "C08_R21", "C08_R20"}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
