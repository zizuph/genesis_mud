//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C36_R21", ({"C36_R20", "C37_R20", "C37_R21",
        "C37_R22", "C36_R22", "C35_R22", "C35_R21", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
