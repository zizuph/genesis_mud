//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C42_R19", ({0, 0, "C43_R19", "C43_R20",
        "C42_R20", "C41_R20", 0, 0}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
