//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C28_R23", ({0, 0, "C29_R23", "C29_R24",
        "C28_R24", "C27_R24", "C27_R23", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
