//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C17_R22", ({0, 0, "C18_R22", "C18_R23",
        "C17_R23", "C16_R23", "C16_R22", "C16_R21"}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
