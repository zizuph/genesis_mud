//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C19_R22", ({0, 0, "C20_R22", "C20_R23",
        "C19_R23", "C18_R23", "C18_R22", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
