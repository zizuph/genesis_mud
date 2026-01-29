//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C33_R23", ({0, "C34_R22", "C34_R23",
        "C34_R24", "C33_R24", "C32_R24", "C32_R23", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
