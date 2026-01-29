//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C39_R20", ({0, 0, "C40_R20", "C40_R21",
        "C39_R21", "C38_R21", "C38_R20", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
