//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C26_R23", ({0, 0, "C27_R23", "C27_R24",
        "C26_R24", "C25_R24", "C25_R23", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
