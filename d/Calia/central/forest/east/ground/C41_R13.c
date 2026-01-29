//Room type {I}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C41_R13", ({0, 0, "C42_R13", "C42_R14",
        "C41_R14", "C40_R14", "C40_R13", 0}),
        ({"spruce"}), ({"rapids", "east"}));
    }
