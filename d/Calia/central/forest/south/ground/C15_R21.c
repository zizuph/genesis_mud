//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C15_R21", ({0, 0, "C16_R21", "C16_R22",
        "C15_R22", "C14_R22", "C14_R21", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
