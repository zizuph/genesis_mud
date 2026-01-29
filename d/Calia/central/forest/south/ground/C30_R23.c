//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C30_R23", ({0, 0, "C31_R23", "C31_R24",
        "C30_R24", "C29_R24", "C29_R23", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
