//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C46_R18", ({0, "C47_R17", "C47_R18",
        "C47_R19", "C46_R19", "C45_R19", "C45_R18", 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
