//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C48_R16", ({"C48_R15", "C49_R15", "C49_R16",
        "C49_R17", "C48_R17", "C47_R17", "C47_R16", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
