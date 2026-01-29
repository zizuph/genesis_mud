//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C45_R18", ({0, 0, "C46_R18", "C46_R19",
        "C45_R19", "C44_R19", 0, 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
