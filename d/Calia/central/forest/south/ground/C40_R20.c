//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C40_R20", ({0, 0, "C41_R20", "C41_R21",
        "C40_R21", "C39_R21", "C39_R20", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
