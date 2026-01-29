//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C16_R22", ({"C16_R21", 0, "C17_R22",
        "C17_R23", "C16_R23", "C15_R23", "C15_R22", "C15_R21"}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
