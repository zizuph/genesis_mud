//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C34_R21", ({0, 0, "C35_R21", "C35_R22",
        "C34_R22", 0, 0, 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
