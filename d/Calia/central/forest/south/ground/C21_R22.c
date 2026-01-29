//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C21_R22", ({0, 0, "C22_R22", "C22_R23",
        "C21_R23", "C20_R23", "C20_R22", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
