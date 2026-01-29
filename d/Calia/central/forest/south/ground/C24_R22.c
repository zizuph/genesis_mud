//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C24_R22", ({0, 0, 0, "C25_R23", "C24_R23",
        "C23_R23", "C23_R22", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
