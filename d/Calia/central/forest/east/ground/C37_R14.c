//Room type {I}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C37_R14", ({0, 0, "C38_R14", "C38_R15",
        "C37_R15", "C36_R15", "C36_R14", 0}),
        ({"spruce"}), ({"rapids", "east"}));
    }
