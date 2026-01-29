//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C08_R20", ({0, 0, 0, "C09_R21", "C08_R21",
        "C07_R21", "C07_R20", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
