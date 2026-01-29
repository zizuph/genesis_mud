//Room type {I}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C39_R13", ({0, 0, "C40_R13", "C40_R14",
        "C39_R14", "C38_R14", 0, 0}),
        ({"spruce"}), ({"rapids", "east"}));
    }
