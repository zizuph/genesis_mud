//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C47_R16", ({0, "C48_R15", "C48_R16",
        "C48_R17", "C47_R17", 0, 0, 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
