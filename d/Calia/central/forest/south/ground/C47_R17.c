//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C47_R17", ({"C47_R16", "C48_R16", "C48_R17",
        "C48_R18", "C47_R18", "C46_R18", 0, 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
