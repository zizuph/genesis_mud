//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C11_R21", ({0, 0, "C12_R21", "C12_R22",
        "C11_R22", "C10_R22", "C10_R21", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
